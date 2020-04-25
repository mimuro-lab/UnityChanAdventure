 #include "AnimationMove.h"

Define::Status AnimationMove::update(
	Define::Status nowStatus, 
	Define::rollAction_Basic _isAction, 
	std::shared_ptr<CollisionDetect> _collision, 
	std::shared_ptr<Stage> _stage, 
	std::shared_ptr<Animation> _animation
)
{
	Define::Status _nextStatus = nowStatus;

	CollisionDetect::toShiftDirect _to = getToShift(_isAction);
	
	if (getSwitchAction(_isAction))
		pysicQty.refresh(true, false);

	// 次のコマで、y方向にその速度で動いて大丈夫か？もし障壁があったら、、、
	if (_collision->calcShitingCollisionedSide(_to, pysicQty.y_vel) && !getForwardCollisionedSide(_to, _collision))
	{
		//bottom辺の1ブロック上のブロックの下辺座標に移動する。
		int x = nowStatus._x;
		int Forward_Block_nearSideY = getForwardBlockNearSide(nowStatus, _to, pysicQty, _collision, _stage);
		DrawBox(0, Forward_Block_nearSideY - 1, 1000, Forward_Block_nearSideY + 1, GetColor(255, 0, 0), true);
		int y = Forward_Block_nearSideY + getRangeOfNearBlock(_to, pysicQty, _collision);
		_collision->update(pysicQty.setPoint(nowStatus, x, y), _stage);
		pysicQty.refresh(true, true);
		return pysicQty.setPoint(nowStatus, x, y);
	}

	// 速度の方向に障壁が何もなかったらpysicQtyの更新を行う。
	
	// _toの方向に何もない、かつ、_toの方向に座標が移動しているなら更新
	bool forwardCollision = !getForwardCollisionedSide(_to, _collision);
	bool pysicShifting = pysicQty.getShifting(_to, _isAction);
	if (forwardCollision && pysicShifting) {
		return pysicQty.update(
				nowStatus,
				0, 
				getAcc(nowStatus, _isAction), 
				_isInitFroce[static_cast<int>(_isAction)], 
				_validGravityAction[static_cast<int>(_isAction)]
			);
	}
	
	return _nextStatus;
	
}

int AnimationMove::getForwardBlockNearSide(
	Define::Status nowStatus, 
	CollisionDetect::toShiftDirect _to, 
	PysicalQTY _pysic,
	std::shared_ptr<CollisionDetect> _collision, 
	std::shared_ptr<Stage> _stage
)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head:
		return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to) - Define::blockHeight).y2;
		break;
	case CollisionDetect::toShiftDirect::bottom:
		return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to) + Define::blockHeight).y1;
		break;
	case CollisionDetect::toShiftDirect::_vertical://垂直だったら座標がどっちに動いているかで判断（速度０はどっちでも構わないが上に合わせる）
		if(_pysic.y_vel <= 0)
			return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to, _pysic.y_vel) - Define::blockHeight).y2;
		else
			return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to, _pysic.y_vel) + Define::blockHeight).y1;
	}
	return 0;
}

//  _isActionの状態でどの方向に動くアクションなのかを計算する。
CollisionDetect::toShiftDirect AnimationMove::getToShift(Define::rollAction_Basic _isAction)
{
	
	switch (_isAction) {
	case Define::rollAction_Basic::Brake:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Crouch:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Damage:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Idle:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Jump_Fall:
		return CollisionDetect::toShiftDirect::bottom;
		break;
	case Define::rollAction_Basic::Jump_Landing:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Jump_MidAir:
		return CollisionDetect::toShiftDirect::_vertical;
		break;
	case Define::rollAction_Basic::Jump_Up:
		return CollisionDetect::toShiftDirect::head;
		break;
	case Define::rollAction_Basic::Fall:
		return CollisionDetect::toShiftDirect::bottom;
		break;
	case Define::rollAction_Basic::Run:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Walk:
		return CollisionDetect::toShiftDirect::_none;
		break;
	}
	
	return CollisionDetect::toShiftDirect::_none;

}

bool AnimationMove::getForwardCollisionedSide(CollisionDetect::toShiftDirect _to, std::shared_ptr<CollisionDetect> _collision)

{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head:
		return _collision->getCollisionedSide().head;
		break;
	case CollisionDetect::toShiftDirect::bottom:
		return _collision->getCollisionedSide().bottom;
		break;
	case CollisionDetect::toShiftDirect::_vertical:
		return _collision->getCollisionedSide().bottom || _collision->getCollisionedSide().head;
		break;
	}
	return false;
}

int AnimationMove::getRangeOfNearBlock(CollisionDetect::toShiftDirect _to, PysicalQTY _pysic, std::shared_ptr<CollisionDetect> _collision)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head://上のレンガに合わせられるので下向き。
		return _collision->getRange(CollisionDetect::toShiftDirect::head);
		break;
	case CollisionDetect::toShiftDirect::bottom://下のレンガに合わせられるので上向き。
		return -_collision->getRange(CollisionDetect::toShiftDirect::bottom);
		break;
	case CollisionDetect::toShiftDirect::_vertical://垂直だったら座標がどっちに動いているかで判断（速度０はどっちでも構わないが上に合わせる）
		if (_pysic.y_vel <= 0)
			return _collision->getRange(CollisionDetect::toShiftDirect::head);
		else
			return -_collision->getRange(CollisionDetect::toShiftDirect::bottom);
		break;
	}
	return 0;
}

char AnimationMove::getAcc(Define::Status nowStatus, Define::rollAction_Basic _isAction)
{
	switch (_isAction) {
	case Define::rollAction_Basic::Jump_MidAir:
		return 0;
		break;
	case Define::rollAction_Basic::Jump_Up:
		return 0;
		break;
	case Define::rollAction_Basic::Fall:
		return 0;
		break;
	}
	return 0;
}

