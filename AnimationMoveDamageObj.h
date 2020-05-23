#pragma once
#include "AnimationMove.h"
#include "PysicalDamageObj.h"
#include <memory>

using namespace std;

class AnimationMoveDamageObj :
	public AnimationMove
{
	shared_ptr<PysicalDamageObj> damagePysic;
public:
	AnimationMoveDamageObj(int initVelX, int initVelY, bool isDireRight) {
		damagePysic = make_shared<PysicalDamageObj>(initVelX, initVelY, isDireRight);
	}
	~AnimationMoveDamageObj() = default;

	Status update(
		Status nowStatus,
		characterAction _isAction,
		shared_ptr<CollisionDetect> _collision,
		shared_ptr<Stage> _stage,
		shared_ptr<Animation> _animation, 
		VirtualController controller) override;
};

