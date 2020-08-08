#include "AnimationSwitchSword.h"

shared_ptr<Animation> AnimationSwitchSword::switchingAnimation(characterAction next, Status nowStatus)
{
	using namespace std;

	shared_ptr<Animation> retObj;
	
	
	switch (next) {
	case characterAction::Brake:
		nowAction = characterAction::Brake;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Crouch:
		nowAction = characterAction::Crouch;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Damage:
		nowAction = characterAction::Damage;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Idle:
		nowAction = characterAction::Idle;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Jump_Fall:
		nowAction = characterAction::Jump_Fall;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Jump_Landing:
		nowAction = characterAction::Jump_Landing;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Jump_MidAir:
		nowAction = characterAction::Jump_MidAir;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Jump_Up:
		nowAction = characterAction::Jump_Up;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Fall:
		nowAction = characterAction::Fall;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Run:
		nowAction = characterAction::Run;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Walk:
		nowAction = characterAction::Walk;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Hundgun_init:
		nowAction = characterAction::Hundgun_init;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Hundgun_end:
		nowAction = characterAction::Hundgun_end;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Hundgun_horizonal:
		nowAction = characterAction::Hundgun_horizonal;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Soard1_init:
		nowAction = characterAction::Soard1_init;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Soard1_end:
		nowAction = characterAction::Soard1_end;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Soard2_init:
		nowAction = characterAction::Soard2_init;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	case characterAction::Soard3_init:
		nowAction = characterAction::Soard3_init;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
		break;
	default:
		nowAction = characterAction::Idle;
		retObj = make_shared <Animation>(ImagePath_Effect::getIns()->star_pink, nowStatus, 0, 0, 1, 99, true, 0.1);
	}

	retObj->arrangeScale(0.3);

	if(nowStatus.directRight)
		retObj->arrangeRotation(30);
	else
		retObj->arrangeRotation(-30);

	return retObj;
}