#include "AnimationMove.h"

Define::Status AnimationMove::updateBrake(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	return nowStatus;
}

Define::Status AnimationMove::updateCrouch(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	return nowStatus;
}

Define::Status AnimationMove::updateDamage(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	return nowStatus;
}

Define::Status AnimationMove::updateIdle(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{

	return nowStatus;
}

Define::Status AnimationMove::updateJump_Fall(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	return nowStatus;
}

Define::Status AnimationMove::updateJump_Landing(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	return nowStatus;
}

Define::Status AnimationMove::updateJump_MidAir(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = nowStatus;
	_nextStatus._y -= velocity.basicAction.jump_midAir;
	return _nextStatus;
}

Define::Status AnimationMove::updateJump_Up(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = nowStatus;
	_nextStatus._y -= velocity.basicAction.jump_up;
	return _nextStatus;
}

Define::Status AnimationMove::updateFall(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = nowStatus;
	_nextStatus._y++;
	if (_collision->getCollisionedSide().bottom)
		return nowStatus;
	return _nextStatus;
	return nowStatus;
}

Define::Status AnimationMove::updateRun(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = nowStatus;
	if (nowStatus.directRight) {
		_nextStatus._x += velocity.basicAction.run;
		_collision->update(_nextStatus, _stage);
		if (_collision->getCollisionedSide().right)
			return nowStatus;
		return _nextStatus;
	}
	else {
		_nextStatus._x -= velocity.basicAction.run;
		_collision->update(_nextStatus, _stage);
		if (_collision->getCollisionedSide().left)
			return nowStatus;
		return _nextStatus;
	}
	return nowStatus;
}

Define::Status AnimationMove::updateWalk(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = nowStatus;
	if (nowStatus.directRight) {
		_nextStatus._x += velocity.basicAction.walk;
		_collision->update(_nextStatus, _stage);
		if (_collision->getCollisionedSide().right)
			return nowStatus;
		return _nextStatus;
	}
	else {
		_nextStatus._x -= velocity.basicAction.walk;
		_collision->update(_nextStatus, _stage);
		if (_collision->getCollisionedSide().left)
			return nowStatus;
		return _nextStatus;
	}
	return nowStatus;
}