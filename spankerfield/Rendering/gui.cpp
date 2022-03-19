#include "gui.h"
#include "renderer.h"
#include "../common.h"
#include "../ImGui/imgui.h"
#include "../settings.h"
#include "../global.h"
#include "../Features/main.h"

namespace big
{
	void gui::dx_init()
	{
		auto& style = ImGui::GetStyle();
		style.FrameRounding = 4.0f;
		style.WindowBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.GrabRounding = 4.0f;
		style.WindowPadding = { 10.f, 10.f };
		style.PopupRounding = 0.f;
		style.FramePadding = { 8.f, 4.f };
		style.ItemSpacing = { 10.f, 8.f };
		style.ItemInnerSpacing = { 6.f, 6.f };
		style.TouchExtraPadding = { 0.f, 0.f };
		style.IndentSpacing = 21.f;
		style.ScrollbarSize = 15.f;
		style.GrabMinSize = 8.f;
		style.ChildBorderSize = 0.f;
		style.FrameBorderSize = 0.f;
		style.TabBorderSize = 0.f;
		style.WindowRounding = 4.f;
		style.ChildRounding = 3.f;
		style.ScrollbarRounding = 4.f;
		style.TabRounding = 4.f;
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.DisplaySafeAreaPadding = { 3.f, 3.f };

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		colors[ImGuiCol_TextDisabled] = ImColor(42, 42, 42);
		colors[ImGuiCol_WindowBg] = ImColor(18, 12, 27);
		colors[ImGuiCol_ChildBg] = ImColor(18, 12, 27);
		colors[ImGuiCol_PopupBg] = ImColor(18, 12, 27);
		colors[ImGuiCol_Border] = ImColor(35, 32, 40);
		colors[ImGuiCol_BorderShadow] = ImColor(35, 32, 40);
		colors[ImGuiCol_FrameBg] = ImColor(35, 42, 106);
		colors[ImGuiCol_FrameBgHovered] = ImColor(35, 42, 106);
		colors[ImGuiCol_FrameBgActive] = ImColor(34, 122, 180);
		colors[ImGuiCol_TitleBg] = ImColor(39, 51, 125);
		colors[ImGuiCol_TitleBgActive] = ImColor(39, 51, 125);
		colors[ImGuiCol_TitleBgCollapsed] = ImColor(39, 51, 125);
		colors[ImGuiCol_MenuBarBg] = ImColor(39, 51, 125);
		colors[ImGuiCol_ScrollbarBg] = ImColor(18, 12, 27);
		colors[ImGuiCol_ScrollbarGrab] = ImColor(18, 12, 27);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(34, 122, 180);
		colors[ImGuiCol_ScrollbarGrabActive] = ImColor(34, 122, 180);
		colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
		colors[ImGuiCol_SliderGrab] = ImColor(33, 107, 167);
		colors[ImGuiCol_SliderGrabActive] = ImColor(27, 100, 151);
		colors[ImGuiCol_Button] = ImColor(33, 43, 105);
		colors[ImGuiCol_ButtonHovered] = ImColor(29, 100, 150);
		colors[ImGuiCol_ButtonActive] = ImColor(27, 100, 151);
		colors[ImGuiCol_Header] = ImColor(34, 122, 180);
		colors[ImGuiCol_HeaderHovered] = ImColor(29, 100, 150);
		colors[ImGuiCol_HeaderActive] = ImColor(34, 122, 180);
		colors[ImGuiCol_Separator] = ImColor(46, 46, 46);
		colors[ImGuiCol_SeparatorHovered] = ImColor(46, 46, 46);
		colors[ImGuiCol_SeparatorActive] = ImColor(46, 46, 46);
		colors[ImGuiCol_ResizeGrip] = ImColor(46, 46, 46);
		colors[ImGuiCol_ResizeGripHovered] = ImColor(29, 100, 150);
		colors[ImGuiCol_ResizeGripActive] = ImColor(27, 100, 151);
		colors[ImGuiCol_Tab] = ImColor(33, 43, 105);
		colors[ImGuiCol_TabHovered] = ImColor(34, 122, 180);
		colors[ImGuiCol_TabActive] = ImColor(34, 122, 180);
		colors[ImGuiCol_TabUnfocused] = ImColor(33, 43, 105);
		colors[ImGuiCol_TabUnfocusedActive] = ImColor(34, 122, 180);

		ImGui::SetNextWindowSize({ 690, 710 });
		ImGui::SetNextWindowBgAlpha(1.f);
	}

	void gui::dx_on_tick()
	{
		if (ImGui::Begin(xorstr_("Spankerfield##")))
		{
			ImGui::BeginTabBar(xorstr_("tabbar"));

			if (ImGui::BeginTabItem(xorstr_("Main")))
			{
				ImGui::Checkbox(xorstr_("Draw ESP"), &g_settings.esp);
				ImGui::SliderFloat(xorstr_("ESP distance"), &g_settings.esp_distance, 1.f, 10000.f);

				ImGui::Separator();

				ImGui::Checkbox(xorstr_("Draw box"), &g_settings.draw_box);
				ImGui::PushItemWidth(300.f);
				ImGui::SliderInt(xorstr_("Box style"), &g_settings.box_style, 1, 6);
				ImGui::PopItemWidth();

				ImGui::Text(xorstr_("Box color"));
				static float box_colors_oc[4] = { g_settings.box_color_occluded.Value.x, g_settings.box_color_occluded.Value.y, g_settings.box_color_occluded.Value.z, g_settings.box_color_occluded.Value.w };
				if (ImGui::ColorEdit4(xorstr_("Not visible##BX"), box_colors_oc))
					g_settings.box_color_occluded = { box_colors_oc[0], box_colors_oc[1], box_colors_oc[2], box_colors_oc[3] };

				static float box_colors[4] = { g_settings.box_color.Value.x, g_settings.box_color.Value.y, g_settings.box_color.Value.z, g_settings.box_color.Value.w };
				if (ImGui::ColorEdit4(xorstr_("Visible##BX"), box_colors))
					g_settings.box_color = { box_colors[0], box_colors[1], box_colors[2], box_colors[3] };

				ImGui::Checkbox(xorstr_("Draw health"), &g_settings.draw_health);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("Draw name"), &g_settings.draw_name);

				ImGui::Checkbox(xorstr_("Draw distance"), &g_settings.draw_distance);

				ImGui::Separator();

				ImGui::Checkbox(xorstr_("Draw skeleton"), &g_settings.draw_skeleton);
				ImGui::Checkbox(xorstr_("Use skeleton dots"), &g_settings.draw_skeleton);
				ImGui::PushItemWidth(300.f);
				ImGui::SliderFloat(xorstr_("Dots distance"), &g_settings.dots_distance, 1.f, 5000.f);
				ImGui::PopItemWidth();

				ImGui::Separator();

				ImGui::Text(xorstr_("Text color"));
				static float text_color_oc[4] = { g_settings.text_color_occluded.Value.x, g_settings.text_color_occluded.Value.y, g_settings.text_color_occluded.Value.z, g_settings.text_color_occluded.Value.w };
				if (ImGui::ColorEdit4(xorstr_("Not visible##TX"), text_color_oc))
					g_settings.text_color_occluded = { text_color_oc[0], text_color_oc[1], text_color_oc[2], text_color_oc[3] };

				static float text_colors[4] = { g_settings.text_color.Value.x, g_settings.text_color.Value.y, g_settings.text_color.Value.z, g_settings.text_color.Value.w };
				if (ImGui::ColorEdit4(xorstr_("Visible##TX"), text_colors))
					g_settings.text_color = { text_colors[0], text_colors[1], text_colors[2], text_colors[3] };

				ImGui::Text(xorstr_("Skeleton color"));
				static float skeleton_color[4] = { g_settings.skeleton_color.Value.x, g_settings.skeleton_color.Value.y, g_settings.skeleton_color.Value.z, g_settings.skeleton_color.Value.w };
				if (ImGui::ColorEdit4(xorstr_("##SKC"), skeleton_color))
					g_settings.skeleton_color = { skeleton_color[0], skeleton_color[1], skeleton_color[2], skeleton_color[3] };

				ImGui::Separator();

				ImGui::Checkbox(xorstr_("Radar"), &g_settings.radar);
				ImGui::PushItemWidth(300.f);
				ImGui::SliderFloat(xorstr_("X##RDR"), &g_settings.radar_x, 0, g_globals.g_width);
				ImGui::PopItemWidth();
				ImGui::SameLine();
				ImGui::PushItemWidth(300.f);
				ImGui::SliderFloat(xorstr_("Y##RDR"), &g_settings.radar_y, 0, g_globals.g_height);
				ImGui::PopItemWidth();
				ImGui::PushItemWidth(300.f);
				ImGui::SliderFloat(xorstr_("Radar distance"), &g_settings.radar_distance, 1.f, 10000.f);
				ImGui::PopItemWidth();

				ImGui::Separator();

				ImGui::Checkbox(xorstr_("Draw explosives"), &g_settings.explosives);
				ImGui::Checkbox(xorstr_("Jet speed"), &g_settings.jet_speed);

				ImGui::Separator();

				ImGui::Checkbox(xorstr_("Spectator list"), &g_settings.spectator_list);
				ImGui::PushItemWidth(300.f);
				ImGui::SliderFloat(xorstr_("X##SP"), &g_settings.spectator_x, 0, g_globals.g_width);
				ImGui::PopItemWidth();
				ImGui::SameLine();
				ImGui::PushItemWidth(300.f);
				ImGui::SliderFloat(xorstr_("Y##SP"), &g_settings.spectator_y, 0, g_globals.g_height);
				ImGui::PopItemWidth();

				ImGui::Text(xorstr_("Spectators color"));
				static float spectators_color[4] = { g_settings.spectator_color.Value.x, g_settings.spectator_color.Value.y, g_settings.spectator_color.Value.z, g_settings.spectator_color.Value.w };
				if (ImGui::ColorEdit4(xorstr_("##SPC"), spectators_color))
					g_settings.spectator_color = { spectators_color[0], spectators_color[1], spectators_color[2], spectators_color[3] };

				ImGui::Separator();

				ImGui::Checkbox(xorstr_("Auto-spot"), &g_settings.minimap);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("Unspot when OBS is active"), &g_settings.obs_check);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Blacklist")))
			{
				ImGui::Checkbox(xorstr_("Draw blacklisted players"), &g_settings.blacklist);

				ImGui::Separator();

				int selected = 0;
				if (ImGui::TreeNode(xorstr_("Blacklisted players")))
				{
					int i = 0;
					for (const auto& rs : plugins::blacklisted)
					{
						if (ImGui::Selectable(rs.c_str(), false))
						{
							selected = i;
					    }

						i++;
					}

					ImGui::TreePop();
				}

				if (ImGui::Button(xorstr_("Delete player from blacklist")))
					plugins::delete_from_blacklist(plugins::blacklisted.at(selected));

				ImGui::Separator();

				static char nick[50]{};
				ImGui::PushItemWidth(300.f);
				ImGui::InputText(xorstr_("Nickname"), nick, IM_ARRAYSIZE(nick));
				ImGui::PopItemWidth();

				if (ImGui::Button(xorstr_("Add player to blacklist")))
					plugins::add_to_blacklist(nick);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Settings")))
			{
				ImGui::Checkbox(xorstr_("Spectator list dummies"), &g_settings.spectator_list_debug);

				ImGui::Separator();

				if (ImGui::Button(xorstr_("Unload")))
					g_globals.g_running = false;

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}