 #include "AnimationMove.h"

Status AnimationMove::update(
	Status nowStatus, 
	rollAction_Basic nowAction, 
	std::shared_ptr<CollisionDetect> _collision, 
	std::shared_ptr<Stage> _stage, 
	std::shared_ptr<Animation> _animation
)
{
	Status _nextStatus = nowStatus;

	nowPoint.x = nowStatus._x;
	nowPoint.y = nowStatus._y;

	nowVelocity = pysical.update(nowAction, nowStatus.directRight);
	nowVelocity = pysical.resetVector(nowVelocity, _collision);

	nextPoint = predictPoint.update(nowPoint ,nowVelocity, _collision, _stage);

	_nextStatus._x = nextPoint.x;
	_nextStatus._y = nextPoint.y;

	return _nextStatus;
	
}