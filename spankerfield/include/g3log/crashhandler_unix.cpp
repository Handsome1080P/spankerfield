/** ==========================================================================
 * 2011 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
 * with no warranties. This code is yours to share, use and modify with no
 * strings attached and no restrictions or obligations.
 *
 * For more information see g3log/LICENSE or refer refer to http://unlicense.org
 * ============================================================================*/

#include "crashhandler.hpp"
#include "logcapture.hpp"
#include "loglevels.hpp"
#include "logmessage.hpp"

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
#error "crashhandler_unix.cpp used but it's a windows system"
#endif

#include <cxxabi.h>
#include <execinfo.h>
#include <unistd.h>
#include <atomic>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <thread>

// Linux/Clang, OSX/Clang, OSX/gcc
#if (defined(__clang__) || defined(__APPLE__))
#include <sys/ucontext.h>
#else
#include <ucontext.h>
#endif

namespace {

   std::atomic<bool> gBlockForFatal{true};

   const std::map<int, std::string> kSignals = {
      {SIGABRT, "SIGABRT"},
      {SIGFPE, "SIGFPE"},
      {SIGILL, "SIGILL"},
      {SIGSEGV, "SIGSEGV"},
      {SIGTERM, "SIGTERM"},
   };

   std::map<int, std::string> gSignals = kSignals;
   std::map<int, struct sigaction> gSavedSigActions;

   bool shouldDoExit() {
      static std::atomic<uint64_t> firstExit{0};
      auto const count = firstExit.fetch_add(1, std::memory_order_relaxed);
      return (0 == count);
   }

   // Dump of stack,. then exit through g3log background worker
   // ALL thanks to this thread at StackOverflow. Pretty much borrowed from:
   // Ref: http://stackoverflow.com/questions/77005/how-to-generate-a-stacktrace-when-my-gcc-c-app-crashes
   void signalHandler(int signal_number, siginfo_t* /*info*/, void* /*unused_context*/) {

      using namespace g3::internal;

      // Only one signal will be allowed past this point
      if (false == shouldDoExit()) {
         while (shouldBlockForFatalHandling()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
         }
      }

      {
         const auto dump = stackdump();
         std::ostringstream fatal_stream;
         const auto fatal_reason = exitReasonName(g3::internal::FATAL_SIGNAL, signal_number);
         fatal_stream << "Received fatal signal: " << fatal_reason;
         fatal_stream << "(" << signal_number << ")\tPID: " << getpid() << std::endl;
         fatal_stream << "\n***** SIGNAL " << fatal_reason << "(" << signal_number << ")" << std::endl;
         LogCapture trigger(FATAL_SIGNAL, static_cast<g3::SignalType>(signal_number), dump.c_str());
         trigger.stream() << fatal_stream.str();
      }  // message sent to g3LogWorker
      // wait to die
   }

   //
   // Installs FATAL signal handler that is enough to handle most fatal events
   //  on *NIX systems
   void installSignalHandler() {
#if !(defined(DISABLE_FATAL_SIGNALHANDLING))
      struct sigaction action;
      sigemptyset(&action.sa_mask);
      action.sa_sigaction = &signalHandler;  // callback to crashHandler for fatal signals
      // sigaction to use sa_sigaction file. ref: http://www.linuxprogrammingblog.com/code-examples/sigaction
      action.sa_flags = SA_SIGINFO;

      // do it verbose style - install all signal actions
      for (const auto& sig_pair : gSignals) {
         struct sigaction old_action;
         memset(&old_action, 0, sizeof(old_action));

         if (sigaction(sig_pair.first, &action, &old_action) < 0) {
            std::string signalerror = "sigaction - " + sig_pair.second;
            perror(signalerror.c_str());
         } else {
            gSavedSigActions[sig_pair.first] = old_action;
         }
      }
#endif
   }

}  // end anonymous namespace

// Redirecting and using signals. In case of fatal signals g3log should log the fatal signal
// and flush the log queue and then "rethrow" the signal to exit
namespace g3 {
   // References:
   // sigaction : change the default action if a specific signal is received
   //             http://linux.die.net/man/2/sigaction
   //             http://publib.boulder.ibm.com/infocenter/aix/v6r1/index.jsp?topic=%2Fcom.ibm.aix.basetechref%2Fdoc%2Fbasetrf2%2Fsigaction.html
   //
   // signal: http://linux.die.net/man/7/signal and
   //         http://msdn.microsoft.com/en-us/library/xdkz3x12%28vs.71%29.asp
   //
   // memset +  sigemptyset: Maybe unnecessary to do both but there seems to be some confusion here
   //          ,plenty of examples when both or either are used
   //          http://stackoverflow.com/questions/6878546/why-doesnt-parent-process-return-to-the-exact-location-after-handling-signal_number
   namespace internal {

      bool shouldBlockForFatalHandling() {
         return gBlockForFatal;
      }

      /// Generate stackdump. Or in case a stackdump was pre-generated and non-empty just use that one
      /// i.e. the latter case is only for Windows and test purposes
      std::string stackdump(const char* rawdump) {
         if (nullptr != rawdump && !std::string(rawdump).empty()) {
            return {rawdump};
         }
         const size_t max_dump_size = 50;
         void* dump[max_dump_size];
         const size_t size = backtrace(dump, max_dump_size);
         char** messages = backtrace_symbols(dump, static_cast<int>(size));  // overwrite sigaction with caller's address

         // dump stack: skip first frame, since that is here
         std::ostringstream oss;
         for (size_t idx = 1; idx < size && messages != nullptr; ++idx) {
            std::string strMessage{messages[idx]};
            std::string mangled_name, offset;

            /// first look for format that includes brackets "(mangled_name+offset)""
            const auto firstBracket = strMessage.find_last_of('(');
            const auto secondBracket = strMessage.find_last_of(')');
            if (firstBracket != strMessage.npos && secondBracket != strMessage.npos) {
               const auto betweenBrackets = strMessage.substr(firstBracket + 1, secondBracket - firstBracket - 1);
               const auto plusSign = betweenBrackets.find_first_of('+');
               if (plusSign != betweenBrackets.npos) {
                  mangled_name = betweenBrackets.substr(0, plusSign);
                  offset = betweenBrackets.substr(plusSign + 1, betweenBrackets.npos);
               }
            } else {
               /// we did not found brackets, looking for "_mangled_name + offset"
               const auto plusSign = strMessage.find_first_of('+');
               const auto lastUnderscore = strMessage.rfind(" _");
               if (plusSign != strMessage.npos && lastUnderscore != strMessage.npos) {
                  mangled_name = strMessage.substr(lastUnderscore + 1, plusSign - lastUnderscore - 2);
                  offset = strMessage.substr(plusSign + 2, strMessage.npos);
               }
            }

            // if the line could be processed, attempt to demangle the symbol
            if (!mangled_name.empty() && !offset.empty()) {
               int status;
               char* real_name = abi::__cxa_demangle(mangled_name.c_str(), 0, 0, &status);
               // if demangling is successful, output the demangled function name
               if (status == 0) {
                  oss << "\tstack dump [" << idx << "]  " << real_name << " + " << offset << std::endl;
               }  // otherwise, output the mangled function name
               else {
                  oss << "\tstack dump [" << idx << "]  " << mangled_name << " + " << offset << std::endl;
               }
               free(real_name);  // mallocated by abi::__cxa_demangle(...)
            } else {
               // no demangling done -- just dump the whole line
               oss << "\tstack dump [" << idx << "]  " << strMessage << std::endl;
            }
         }  // END: for(size_t idx = 1; idx < size && messages != nullptr; ++idx)
         free(messages);
         return oss.str();
      }

      /// string representation of signal ID
      std::string exitReasonName(const LEVELS& level, g3::SignalType fatal_id) {

         int signal_number = static_cast<int>(fatal_id);
         switch (signal_number) {
         case SIGABRT:
            return "SIGABRT";
            break;
         case SIGFPE:
            return "SIGFPE";
            break;
         case SIGSEGV:
            return "SIGSEGV";
            break;
         case SIGILL:
            return "SIGILL";
            break;
         case SIGTERM:
            return "SIGTERM";
            break;
         default:
            std::ostringstream oss;
            oss << "UNKNOWN SIGNAL(" << signal_number << ") for " << level.text;
            return oss.str();
         }
      }

      // Triggered by g3log->g3LogWorker after receiving a FATAL trigger
      // which is LOG(FATAL), CHECK(false) or a fatal signal our signalhandler caught.
      // --- If LOG(FATAL) or CHECK(false) the signal_number will be SIGABRT
      void exitWithDefaultSignalHandler(const LEVELS& level, g3::SignalType fatal_signal_id) {
         const int signal_number = static_cast<int>(fatal_signal_id);

         // Restore all saved signal handlers. If handling a signal which causes exiting
         // than let the original signal handlers to handle other signals.
         for (const auto& sig : gSignals) {
            restoreSignalHandler(sig.first);
         }

         std::cerr << "\n\n"
                   << __FUNCTION__ << ":" << __LINE__ << ". Exiting due to " << level.text << ", " << signal_number << "   \n\n"
                   << std::flush;

         raise(signal_number);

         // When running as PID1 the above kill doesn't have any effect (execution simply passes through it, contrary
         // to a non-PID1 process where execution stops at kill and switches over to signal handling). Also as PID1
         // we must unblock the thread that received the original signal otherwise the process will never terminate.
         gBlockForFatal = false;

         exit(signal_number);
      }

      // This function is intended to be async-signal-safe. Using write and STDERR_FILENO should be
      // safe in a signal handler. ref: http://pubs.opengroup.org/onlinepubs/009695399/functions/write.html

      // This function is intended to be async-signal-safe.
      // It writes an error message to stderr using the write system call,
      // which is listed as async-signal-safe by POSIX.
      size_t writeErrorMessage(const char* message) {
         if (message == nullptr) {
            return 0;
         }

         // Calculate the length of the message without using std library strlen or similar
         // this is to ensure async-signal-safe by POSIX
         size_t length = 0;
         for (const char* p = message; *p != '\0'; ++p) {
            ++length;
         }

         // Write the message to STDERR_FILENO in a single call.
         // This assumes that the message is not too large for a single write.
         auto bytes_written = write(STDERR_FILENO, message, length);
         return bytes_written;
      }

      // restores the signal handler back to default
      void restoreFatalHandlingToDefault() {
#if !(defined(DISABLE_FATAL_SIGNALHANDLING))
         overrideSetupSignals(kSignals);
#endif
      }

   }  // namespace internal

   std::string signalToStr(int signal_number) {
      std::string signal_name;
      const char* signal_name_sz = strsignal(signal_number);

      // From strsignal(3): On some systems (but not on Linux), NULL may instead
      // be returned for an invalid signal number.
      if (nullptr == signal_name_sz) {
         signal_name = "Unknown signal " + std::to_string(signal_number);
      } else {
         signal_name = signal_name_sz;
      }
      return signal_name;
   }

   void restoreSignalHandler(int signal_number) {
#if !(defined(DISABLE_FATAL_SIGNALHANDLING))
      auto old_action_it = gSavedSigActions.find(signal_number);
      if (old_action_it == gSavedSigActions.end()) {
         return;
      }

      if (sigaction(signal_number, &(old_action_it->second), nullptr) < 0) {
         auto signalname = std::string("sigaction - ") + signalToStr(signal_number);
         // https://man7.org/linux/man-pages/man7/signal-safety.7.html (see signal-safety)
         internal::writeErrorMessage(signalname.c_str());
      }

      gSavedSigActions.erase(old_action_it);
#endif
   }

   // This will override the default signal handler setup and instead
   // install a custom set of signals to handle
   void overrideSetupSignals(const std::map<int, std::string> overrideSignals) {
      static std::mutex signalLock;
      std::lock_guard<std::mutex> guard(signalLock);
      for (const auto& sig : gSignals) {
         restoreSignalHandler(sig.first);
      }

      gSignals = overrideSignals;
      installCrashHandler();  // installs all the signal handling for gSignals
   }

   // installs the signal handling for whatever signal set that is currently active
   // If you want to setup your own signal handling then
   // You should instead call overrideSetupSignals()
   void installCrashHandler() {
      installSignalHandler();
   }
}  // end namespace g3
