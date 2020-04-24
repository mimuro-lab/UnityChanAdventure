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

Define::Status AnimationMove::updateJump_MidAir(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, char _steps)
{
	pysicQty.refresh();
	if (_collision->calcShitingCollisionedSide(CollisionDetect::toShiftDirect::head, pysicQty.y_vel)) {
		pysicQty.refresh();
		//bottom辺の1ブロック上のブロックの下辺座標に移動する。
		int x = nowStatus._x;
		int Head_Block_BottomY = _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getToHead() - Define::blockHeight).y2;
		int y = Head_Block_BottomY - _collision->getToBottom();
		_collision->update(pysicQty.setPoint(nowStatus, x, y), _stage);
		return pysicQty.setPoint(nowStatus, x, y);
	}

	if (!_collision->getCollisionedSide().head) {
		if (counter == 0) {
			counter++;
			return pysicQty.update(nowStatus, 0, -velDef.basicAction.jump_midAir);
		}
		else {
			counter++;
			counter %= _steps;
			return nowStatus;
		}

	}
}

Define::Status AnimationMove::updateJump_Up(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, std::shared_ptr<Animation> _animation)
{
	if (_collision->calcShitingCollisionedSide(CollisionDetect::toShiftDirect::head, pysicQty.y_vel)) {
		pysicQty.refresh();
		//bottom辺の1ブロック上のブロックの下辺座標に移動する。
		int x = nowStatus._x;
		int Head_Block_BottomY = _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getToHead() - Define::blockHeight).y2;
		int y = Head_Block_BottomY - _collision->getToBottom();
		_collision->update(pysicQty.setPoint(nowStatus, x, y), _stage);
		return pysicQty.setPoint(nowStatus, x, y);
	}

	if (!_collision->getCollisionedSide().head) {
		if (counter == 0) {
			counter++;
			return pysicQty.update(nowStatus, 0, -velDef.basicAction.jump_up);
		}
		else {
			counter++;
			counter %= 1;
			return nowStatus;
		}

	}
}

Define::Status AnimationMove::updateFall(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, char _steps)
{
	
	if (_collision->calcShitingCollisionedSide(CollisionDetect::toShiftDirect::bottom, pysicQty.y_vel)) {
		pysicQty.refresh();
		//bottom辺の1ブロック下のブロックの上辺座標に移動する。
		int x = nowStatus._x;
		int bottom_Block_UpY = _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getToBottom() + Define::blockHeight).y1;
		int y = bottom_Block_UpY - _collision->getToBottom();
		_collision->update(pysicQty.setPoint(nowStatus, x, y), _stage);
		return pysicQty.setPoint(nowStatus, x, y);
	}	


	if (!_collision->getCollisionedSide().bottom) {

		if (counter == 0) {
			counter++;
			return pysicQty.update(nowStatus, 0, acc_gravity);
		}
		else {
			counter++;
			counter %= 1;
			return nowStatus;
		}
	}
	return nowStatus;
}

Define::Status AnimationMove::updateRun(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = nowStatus;
	if (nowStatus.directRight) {
		_nextStatus._x += velDef.basicAction.run;
		_collision->update(_nextStatus, _stage);
		if (_collision->getCollisionedSide().right)
			return nowStatus;
		return _nextStatus;
	}
	else {
		_nextStatus._x -= velDef.basicAction.run;
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
		_nextStatus._x += velDef.basicAction.walk;
		_collision->update(_nextStatus, _stage);
		if (_collision->getCollisionedSide().right)
			return nowStatus;
		return _nextStatus;
	}
	else {
		_nextStatus._x -= velDef.basicAction.walk;
		_collision->update(_nextStatus, _stage);
		if (_collision->getCollisionedSide().left)
			return nowStatus;
		return _nextStatus;
	}
	return nowStatus;
}