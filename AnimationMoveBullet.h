#pragma once
#include "AnimationMove.h"
#include "PysicalBullet.h"
#include <memory>

using namespace std;

class AnimationMoveBullet :
	public AnimationMove
{
	shared_ptr<PysicalBullet> damagePysic;
public:
	AnimationMoveBullet(int initVelX, int initVelY, bool isDireRight) {
		damagePysic = make_shared<PysicalBullet>(initVelX, initVelY, isDireRight);
	}
	~AnimationMoveBullet() = default;

	Status update(
		Status nowStatus,
		characterAction _isAction,
		shared_ptr<CollisionDetect> _collision,
		shared_ptr<Stage> _stage,
		shared_ptr<Animation> _animation, 
		VirtualController controller) override;
};

