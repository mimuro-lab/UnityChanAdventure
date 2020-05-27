#pragma once
#include "AnimationMove.h"
#include "PysicalSword.h"
#include <memory>

using namespace std;

class AnimationMoveSword
	:public AnimationMove
{
	shared_ptr<PysicalSword> damagePysic;
public:
	AnimationMoveSword(int initVelX, int initVelY, bool isDireRight) {
		damagePysic = make_shared<PysicalSword>(initVelX, initVelY, isDireRight);
	}

	Status update(
		Status nowStatus,
		characterAction _isAction,
		shared_ptr<CollisionDetect> _collision,
		shared_ptr<Stage> _stage,
		shared_ptr<Animation> _animation,
		VirtualController controller,
		Status playerStatus);
};