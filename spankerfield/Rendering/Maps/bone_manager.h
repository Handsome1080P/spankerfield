#pragma once
#include "../../SDK/sdk.h"

// Honestly this is utterly fucking retarded
std::map<UpdatePoseResultData::BONES, std::string> bone_map
{
	{ UpdatePoseResultData::BONES::Reference, xorstr_("Reference") },
	{ UpdatePoseResultData::BONES::AITrajectory, xorstr_("AI Trajectory") },
	{ UpdatePoseResultData::BONES::Trajectory, xorstr_("Trajectory") },
	{ UpdatePoseResultData::BONES::TrajectoryEnd, xorstr_("Trajectory End") },
	{ UpdatePoseResultData::BONES::Hips, xorstr_("Hips") },
	{ UpdatePoseResultData::BONES::Spine, xorstr_("Lower spine") },
	{ UpdatePoseResultData::BONES::Spine1, xorstr_("Middle spine") },
	{ UpdatePoseResultData::BONES::Spine2, xorstr_("Upper spine") },
	{ UpdatePoseResultData::BONES::LeftShoulder, xorstr_("Left shoulder") },
	{ UpdatePoseResultData::BONES::LeftArm, xorstr_("Left arm") },
	{ UpdatePoseResultData::BONES::LeftArmRoll, xorstr_("Left arm roll") },
	{ UpdatePoseResultData::BONES::LeftForeArm, xorstr_("Left forearm") },
	{ UpdatePoseResultData::BONES::LeftForeArmRoll, xorstr_("Left forearm roll") },
	{ UpdatePoseResultData::BONES::LeftForeArmRoll1, xorstr_("Left forearm roll 1") },
	{ UpdatePoseResultData::BONES::LeftHand, xorstr_("Left hand") },
	{ UpdatePoseResultData::BONES::LeftHandMiddle0, xorstr_("Left hand middle 0") },
	{ UpdatePoseResultData::BONES::LeftHandMiddle1, xorstr_("Left hand middle 1") },
	{ UpdatePoseResultData::BONES::LeftHandMiddle2, xorstr_("Left hand middle 2") },
	{ UpdatePoseResultData::BONES::LeftHandMiddle3, xorstr_("Left hand middle 3") },
	{ UpdatePoseResultData::BONES::LeftHandMiddle4, xorstr_("Left hand middle 4") },
	{ UpdatePoseResultData::BONES::LeftHandRing0, xorstr_("Left hand ring 0") },
	{ UpdatePoseResultData::BONES::LeftHandRing1, xorstr_("Left hand ring 1") },
	{ UpdatePoseResultData::BONES::LeftHandRing2, xorstr_("Left hand ring 2") },
	{ UpdatePoseResultData::BONES::LeftHandRing3, xorstr_("Left hand ring 3") },
	{ UpdatePoseResultData::BONES::LeftHandRing4, xorstr_("Left hand ring 4") },
	{ UpdatePoseResultData::BONES::LeftHandPinky0, xorstr_("Left hand pinky 0") },
	{ UpdatePoseResultData::BONES::LeftHandPinky1, xorstr_("Left hand pinky 1") },
	{ UpdatePoseResultData::BONES::LeftHandPinky2, xorstr_("Left hand pinky 2") },
	{ UpdatePoseResultData::BONES::LeftHandPinky3, xorstr_("Left hand pinky 3") },
	{ UpdatePoseResultData::BONES::LeftHandPinky4, xorstr_("Left hand pinky 4") },
	{ UpdatePoseResultData::BONES::LeftHandIndex0, xorstr_("Left hand index 0") },
	{ UpdatePoseResultData::BONES::LeftHandIndex1, xorstr_("Left hand index 1") },
	{ UpdatePoseResultData::BONES::LeftHandIndex2, xorstr_("Left hand index 2") },
	{ UpdatePoseResultData::BONES::LeftHandIndex3, xorstr_("Left hand index 3") },
	{ UpdatePoseResultData::BONES::LeftHandIndex4, xorstr_("Left hand index 4") },
	{ UpdatePoseResultData::BONES::LeftHandThumb1, xorstr_("Left hand thumb 1") },
	{ UpdatePoseResultData::BONES::LeftHandThumb2, xorstr_("Left hand thumb 2") },
	{ UpdatePoseResultData::BONES::LeftHandThumb3, xorstr_("Left hand thumb 3") },
	{ UpdatePoseResultData::BONES::LeftHandThumb4, xorstr_("Left hand thumb 4") },
	{ UpdatePoseResultData::BONES::LeftHandProp1, xorstr_("Left hand prop 1") },
	{ UpdatePoseResultData::BONES::LeftElbowRoll, xorstr_("Left elbow roll") },
	{ UpdatePoseResultData::BONES::LeftArmCloth, xorstr_("Left arm cloth") },
	{ UpdatePoseResultData::BONES::LeftShoulderPhys1, xorstr_("Left shoulder phys 1") },
	{ UpdatePoseResultData::BONES::Neck, xorstr_("Neck") },
	{ UpdatePoseResultData::BONES::Neck1, xorstr_("Neck 1") },
	{ UpdatePoseResultData::BONES::Head, xorstr_("Head") },
	{ UpdatePoseResultData::BONES::HeadEnd, xorstr_("Head end") },
	{ UpdatePoseResultData::BONES::Face, xorstr_("Face") },
	{ UpdatePoseResultData::BONES::Jaw, xorstr_("Jaw") },
	{ UpdatePoseResultData::BONES::LeftLowerLip, xorstr_("Left lower lip") },
	{ UpdatePoseResultData::BONES::LeftLowerInnerLip, xorstr_("Left lower inner lip") },
	{ UpdatePoseResultData::BONES::LowerLip, xorstr_("Lower lip") },
	{ UpdatePoseResultData::BONES::LowerInnerLip, xorstr_("Lower inner lip") },
	{ UpdatePoseResultData::BONES::RightLowerLip, xorstr_("Right lower lip") },
	{ UpdatePoseResultData::BONES::RightLowerInnerLip, xorstr_("Right lower inner lip") },
	{ UpdatePoseResultData::BONES::Tongue, xorstr_("Tongue") },
	{ UpdatePoseResultData::BONES::TongueTip, xorstr_("Tongue tip") },
	{ UpdatePoseResultData::BONES::Chin, xorstr_("Chin") },
	{ UpdatePoseResultData::BONES::LeftLowCheek, xorstr_("Left low cheek") },
	{ UpdatePoseResultData::BONES::RightLowCheek, xorstr_("Right low cheek") },
	{ UpdatePoseResultData::BONES::LeftEye, xorstr_("Left eye") },
	{ UpdatePoseResultData::BONES::LeftIris, xorstr_("Left iris") },
	{ UpdatePoseResultData::BONES::RightEye, xorstr_("Right eye") },
	{ UpdatePoseResultData::BONES::RightIris, xorstr_("Right iris") },
	{ UpdatePoseResultData::BONES::LeftUpCheek, xorstr_("Left upper cheek") },
	{ UpdatePoseResultData::BONES::LeftUpInnerCheek, xorstr_("Left upper inner cheek") },
	{ UpdatePoseResultData::BONES::RightUpInnerCheek, xorstr_("Right upper inner cheek") },
	{ UpdatePoseResultData::BONES::RightUpCheek, xorstr_("Right upper cheek") },
	{ UpdatePoseResultData::BONES::LeftCheek, xorstr_("Left cheek") },
	{ UpdatePoseResultData::BONES::RightCheek, xorstr_("Right cheek") },
	{ UpdatePoseResultData::BONES::LeftMouth, xorstr_("Left mouth") },
	{ UpdatePoseResultData::BONES::LeftInnerMouth, xorstr_("Left inner mouth") },
	{ UpdatePoseResultData::BONES::LeftMiddleCrease, xorstr_("Left middle crease") },
	{ UpdatePoseResultData::BONES::LeftUpperLip, xorstr_("Left upper lip") },
	{ UpdatePoseResultData::BONES::LeftUpperInnerLip, xorstr_("Left upper inner lip") },
	{ UpdatePoseResultData::BONES::UpperLip, xorstr_("Upper lip") },
	{ UpdatePoseResultData::BONES::UpperInnerLip, xorstr_("Upper inner lip") },
	{ UpdatePoseResultData::BONES::RightUpperLip, xorstr_("Right upper lip") },
	{ UpdatePoseResultData::BONES::RightUpperInnerLip, xorstr_("Right upper inner lip") },
	{ UpdatePoseResultData::BONES::RightMouth, xorstr_("Right mouth") },
	{ UpdatePoseResultData::BONES::RightInnerMouth, xorstr_("Right inner mouth") },
	{ UpdatePoseResultData::BONES::RightMiddleCrease, xorstr_("Right middle crease") },
	{ UpdatePoseResultData::BONES::LeftUpEyelid, xorstr_("Left upper eyelid") },
	{ UpdatePoseResultData::BONES::RightUpEyelid, xorstr_("Right upper eyelid") },
	{ UpdatePoseResultData::BONES::LeftLowEyelid, xorstr_("Left lower eyelid") },
	{ UpdatePoseResultData::BONES::RightLowEyelid, xorstr_("Right lower eyelid") },
	{ UpdatePoseResultData::BONES::LeftInnerEyebrow, xorstr_("Left inner eyebrow") },
	{ UpdatePoseResultData::BONES::LeftOuterEyebrow, xorstr_("Left outer eyebrow") },
	{ UpdatePoseResultData::BONES::RightInnerEyebrow, xorstr_("Right inner eyebrow") },
	{ UpdatePoseResultData::BONES::RightOuterEyebrow, xorstr_("Right outer eyebrow") },
	{ UpdatePoseResultData::BONES::LeftNose, xorstr_("Left nose") },
	{ UpdatePoseResultData::BONES::RightNose, xorstr_("Right nose") },
	{ UpdatePoseResultData::BONES::LeftCrease, xorstr_("Left crease") },
	{ UpdatePoseResultData::BONES::RightCrease, xorstr_("Right crease") },
	{ UpdatePoseResultData::BONES::LeftLowMiddleEyebrow, xorstr_("Left low middle eyebrow") },
	{ UpdatePoseResultData::BONES::RightMiddleEyebrow, xorstr_("Right middle eyebrow") },
	{ UpdatePoseResultData::BONES::LeftLowEyelidCrease, xorstr_("Left low eyelid crease") },
	{ UpdatePoseResultData::BONES::LeftLowOuterEyebrow, xorstr_("Left low outer eyebrow") },
	{ UpdatePoseResultData::BONES::NoseTip, xorstr_("Nose tip") },
	{ UpdatePoseResultData::BONES::RightLowOuterEyebrow, xorstr_("Right low outer eyebrow") },
	{ UpdatePoseResultData::BONES::LeftMiddleEyebrow, xorstr_("Left middle eyebrow") },
	{ UpdatePoseResultData::BONES::RightLowMiddleEyebrow, xorstr_("Right low middle eyebrow") },
	{ UpdatePoseResultData::BONES::RightLowEyelidCrease , xorstr_("Right low eyelid crease") },
	{ UpdatePoseResultData::BONES::LowNose, xorstr_("Low nose") },
	{ UpdatePoseResultData::BONES::HeadCloth, xorstr_("Head cloth") },
	{ UpdatePoseResultData::BONES::Throat, xorstr_("Throat") },
	{ UpdatePoseResultData::BONES::Spine2Phys1, xorstr_("Spine 2 Phys 1") },
	{ UpdatePoseResultData::BONES::Spine2Prop1, xorstr_("Spine 2 Prop 1") },
	{ UpdatePoseResultData::BONES::RightShoulder, xorstr_("Right shoulder") },
	{ UpdatePoseResultData::BONES::RightArm, xorstr_("Right arm") },
	{ UpdatePoseResultData::BONES::RightArmRoll, xorstr_("Right arm roll") },
	{ UpdatePoseResultData::BONES::RightForeArm, xorstr_("Right forearm") },
	{ UpdatePoseResultData::BONES::RightForeArmRoll, xorstr_("Right forearm roll") },
	{ UpdatePoseResultData::BONES::RightForeArmRoll1, xorstr_("Right forearm roll 1") },
	{ UpdatePoseResultData::BONES::RightHand, xorstr_("Right hand") },
	{ UpdatePoseResultData::BONES::RightHandMiddle0, xorstr_("Right hand middle 0") },
	{ UpdatePoseResultData::BONES::RightHandMiddle1, xorstr_("Right hand middle 1") },
	{ UpdatePoseResultData::BONES::RightHandMiddle2, xorstr_("Right hand middle 2") },
	{ UpdatePoseResultData::BONES::RightHandMiddle3, xorstr_("Right hand middle 3") },
	{ UpdatePoseResultData::BONES::RightHandMiddle4, xorstr_("Right hand middle 4") },
	{ UpdatePoseResultData::BONES::RightHandRing0, xorstr_("Right hand ring 0") },
	{ UpdatePoseResultData::BONES::RightHandRing1, xorstr_("Right hand ring 1") },
	{ UpdatePoseResultData::BONES::RightHandRing2, xorstr_("Right hand ring 2") },
	{ UpdatePoseResultData::BONES::RightHandRing3, xorstr_("Right hand ring 3") },
	{ UpdatePoseResultData::BONES::RightHandRing4, xorstr_("Right hand ring 4") },
	{ UpdatePoseResultData::BONES::RightHandPinky0, xorstr_("Right hand pinky 0") },
	{ UpdatePoseResultData::BONES::RightHandPinky1, xorstr_("Right hand pinky 1") },
	{ UpdatePoseResultData::BONES::RightHandPinky2, xorstr_("Right hand pinky 2") },
	{ UpdatePoseResultData::BONES::RightHandPinky3, xorstr_("Right hand pinky 3") },
	{ UpdatePoseResultData::BONES::RightHandPinky4, xorstr_("Right hand pinky 4") },
	{ UpdatePoseResultData::BONES::RightHandIndex0, xorstr_("Right hand index 0") },
	{ UpdatePoseResultData::BONES::RightHandIndex1, xorstr_("Right hand index 1") },
	{ UpdatePoseResultData::BONES::RightHandIndex2, xorstr_("Right hand index 2") },
	{ UpdatePoseResultData::BONES::RightHandIndex3, xorstr_("Right hand index 3") },
	{ UpdatePoseResultData::BONES::RightHandIndex4, xorstr_("Right hand index 4") },
	{ UpdatePoseResultData::BONES::RightHandThumb1, xorstr_("Right hand thumb 1") },
	{ UpdatePoseResultData::BONES::RightHandThumb2, xorstr_("Right hand thumb 2") },
	{ UpdatePoseResultData::BONES::RightHandThumb3, xorstr_("Right hand thumb 3") },
	{ UpdatePoseResultData::BONES::RightHandThumb4, xorstr_("Right hand thumb 4") },
	{ UpdatePoseResultData::BONES::RightHandProp1, xorstr_("Right hand prop 1") },
	{ UpdatePoseResultData::BONES::RightElbowRoll, xorstr_("Right elbow roll") },
	{ UpdatePoseResultData::BONES::RightArmCloth, xorstr_("Right arm cloth") },
	{ UpdatePoseResultData::BONES::RightShoulderPhys1, xorstr_("Right shoulder phys 1") },
	{ UpdatePoseResultData::BONES::Wep_Root, xorstr_("Weapon root") },
	{ UpdatePoseResultData::BONES::Wep_Trigger, xorstr_("Weapon trigger") },
	{ UpdatePoseResultData::BONES::Wep_Slide, xorstr_("Weapon slide") },
	{ UpdatePoseResultData::BONES::Wep_Grenade1, xorstr_("Weapon grenade 1") },
	{ UpdatePoseResultData::BONES::Wep_Grenade2, xorstr_("Weapon grenade 2") },
	{ UpdatePoseResultData::BONES::Wep_Mag, xorstr_("Weapon mag") },
	{ UpdatePoseResultData::BONES::Wep_Mag_Ammo, xorstr_("Weapon mag ammo") },
	{ UpdatePoseResultData::BONES::Wep_Mag_Extra1, xorstr_("Weapon mag extra") },
	{ UpdatePoseResultData::BONES::Wep_Scope1, xorstr_("Weapon scope 1") },
	{ UpdatePoseResultData::BONES::Wep_Scope2, xorstr_("Weapon scope 2") },
	{ UpdatePoseResultData::BONES::Wep_Belt1, xorstr_("Weapon belt 1") },
	{ UpdatePoseResultData::BONES::Wep_Belt2, xorstr_("Weapon belt 2") },
	{ UpdatePoseResultData::BONES::Wep_Belt3, xorstr_("Weapon belt 3") },
	{ UpdatePoseResultData::BONES::Wep_Belt4, xorstr_("Weapon belt 4") },
	{ UpdatePoseResultData::BONES::Wep_Belt5, xorstr_("Weapon belt 5") },
	{ UpdatePoseResultData::BONES::Wep_Belt6, xorstr_("Weapon belt 6") },
	{ UpdatePoseResultData::BONES::Wep_Belt7, xorstr_("Weapon belt 7") },
	{ UpdatePoseResultData::BONES::Wep_Belt8, xorstr_("Weapon belt 8") },
	{ UpdatePoseResultData::BONES::Wep_Belt9, xorstr_("Weapon belt 9") },
	{ UpdatePoseResultData::BONES::Wep_Belt10, xorstr_("Weapon belt 10") },
	{ UpdatePoseResultData::BONES::Wep_Bipod1, xorstr_("Weapon bipod 1") },
	{ UpdatePoseResultData::BONES::Wep_Bipod2, xorstr_("Weapon bipod 2") },
	{ UpdatePoseResultData::BONES::Wep_Bipod3, xorstr_("Weapon bipod 3") },
	{ UpdatePoseResultData::BONES::IK_Joint_LeftHand, xorstr_("Left hand joint") },
	{ UpdatePoseResultData::BONES::IK_Joint_RightHand, xorstr_("Right hand joint") },
	{ UpdatePoseResultData::BONES::Wep_Physic1, xorstr_("Weapon physic 1") },
	{ UpdatePoseResultData::BONES::Wep_Physic2, xorstr_("Weapon physic 2") },
	{ UpdatePoseResultData::BONES::Wep_Physic3, xorstr_("Weapon physic 3") },
	{ UpdatePoseResultData::BONES::Wep_Physic4, xorstr_("Weapon physic 4") },
	{ UpdatePoseResultData::BONES::Wep_Physic5, xorstr_("Weapon physic 5") },
	{ UpdatePoseResultData::BONES::Wep_Extra1, xorstr_("Weapon extra 1") },
	{ UpdatePoseResultData::BONES::Wep_Extra2, xorstr_("Weapon extra 2") },
	{ UpdatePoseResultData::BONES::Wep_Extra3, xorstr_("Weapon extra 3") },
	{ UpdatePoseResultData::BONES::Wep_Extra4, xorstr_("Weapon extra 4") },
	{ UpdatePoseResultData::BONES::Wep_Extra5, xorstr_("Weapon extra 5") },
	{ UpdatePoseResultData::BONES::Wep_Aim, xorstr_("Weapon aim") },
	{ UpdatePoseResultData::BONES::LeftSpine1Phys1, xorstr_("Left spine 1 phys 1") },
	{ UpdatePoseResultData::BONES::RightSpine1Phys1, xorstr_("Right spine 1 phys 1") },
	{ UpdatePoseResultData::BONES::LeftUpLeg, xorstr_("Left upper leg") },
	{ UpdatePoseResultData::BONES::LeftUpLegRoll, xorstr_("Left upper leg roll") },
	{ UpdatePoseResultData::BONES::LeftLeg, xorstr_("Left leg") },
	{ UpdatePoseResultData::BONES::LeftFoot, xorstr_("Left foot") },
	{ UpdatePoseResultData::BONES::LeftToeBase, xorstr_("Left toe base") },
	{ UpdatePoseResultData::BONES::LeftToe, xorstr_("Left toe") },
	{ UpdatePoseResultData::BONES::LeftLegCloth, xorstr_("Left leg cloth") },
	{ UpdatePoseResultData::BONES::LeftKneeRoll, xorstr_("Left knee roll") },
	{ UpdatePoseResultData::BONES::LeftHipsRoll, xorstr_("Left hips roll") },
	{ UpdatePoseResultData::BONES::LeftUpLegCloth, xorstr_("Left upper leg cloth") },
	{ UpdatePoseResultData::BONES::HipsCloth, xorstr_("Hips cloth") },
	{ UpdatePoseResultData::BONES::LeftHipsFrontPhys, xorstr_("Left hips front phys") },
	{ UpdatePoseResultData::BONES::LeftHipsBackPhys, xorstr_("Left hips back phys") },
	{ UpdatePoseResultData::BONES::LeftHipsSidePhys, xorstr_("Left hips side phys") },
	{ UpdatePoseResultData::BONES::RightUpLeg, xorstr_("Right upper leg") },
	{ UpdatePoseResultData::BONES::RightUpLegRoll, xorstr_("Right upper leg roll") },
	{ UpdatePoseResultData::BONES::RightLeg, xorstr_("Right leg") },
	{ UpdatePoseResultData::BONES::RightFoot, xorstr_("Right foot") },
	{ UpdatePoseResultData::BONES::RightToeBase, xorstr_("Right toe base") },
	{ UpdatePoseResultData::BONES::RightToe, xorstr_("Right toe") },
	{ UpdatePoseResultData::BONES::RightLegCloth, xorstr_("Right leg cloth") },
	{ UpdatePoseResultData::BONES::RightKneeRoll, xorstr_("Right knee roll") },
	{ UpdatePoseResultData::BONES::RightHipsRoll, xorstr_("Right hips roll") },
	{ UpdatePoseResultData::BONES::RightUpLegCloth, xorstr_("Right upper leg cloth") },
	{ UpdatePoseResultData::BONES::RightHipsFrontPhys, xorstr_("Right hips front phys") },
	{ UpdatePoseResultData::BONES::RightHipsBackPhys, xorstr_("Right hips back phys") },
	{ UpdatePoseResultData::BONES::RightHipsSidePhys, xorstr_("Right hips side phys") },
	{ UpdatePoseResultData::BONES::CameraBase, xorstr_("Camera base") },
	{ UpdatePoseResultData::BONES::CameraJoint, xorstr_("Camera joint") },
	{ UpdatePoseResultData::BONES::Connect, xorstr_("Connect") },
	{ UpdatePoseResultData::BONES::ConnectEnd, xorstr_("Connect end") },
	{ UpdatePoseResultData::BONES::FacePosesAnimation, xorstr_("Face poses animation") }
};