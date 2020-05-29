#pragma once
#include "AnimationSwitch.h"
#include "ImagePath_Object.h"

class AnimationSwitchBullet :
	public AnimationSwitch
{
public:
	AnimationSwitchBullet() : AnimationSwitch(characterAction::Fall){
	}
	~AnimationSwitchBullet() = default;

	shared_ptr<Animation> switchingAnimation(characterAction next, Status _playerStatus) override;
};
