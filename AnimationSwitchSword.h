#pragma once
#include "AnimationSwitch.h"
#include "ImagePath_Effect.h"

class AnimationSwitchSword 
	:	public AnimationSwitch
{
public:
	AnimationSwitchSword() {}
	~AnimationSwitchSword() = default;

	shared_ptr<Animation> switchingAnimation(characterAction next, Status _playerStatus) override;
};

