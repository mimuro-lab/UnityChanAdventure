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

	_nextStatus._y_speed = pysicQty.y_vel;
	_nextStatus._x_speed = pysicQty.x_vel;

	// 状態がBrakeだったらpysicQtyのリセットを行い、終了
	// または、プレイヤーオブジェクトの向くべき方向と速度方向が異なる場合は水平方向のリフレッシュを行う。
	if (_isAction == Define::rollAction_Basic::Brake) {
		pysicQty.refreshVel(true, true, true);
	}// または、プレイヤーオブジェクトの向くべき方向と速度方向が異なる場合は水平方向のリフレッシュを行う。
	// ※walk→idlingと切り替わった後、速度が残っている状態で、逆方向に歩こうとしたときこの条件を満たす。
	else if (
		(nowStatus.directRight && nowStatus._x_speed < 0) ||
		(!nowStatus.directRight && nowStatus._x_speed > 0)
		) {
		pysicQty.refreshVel(false, true, true);
	}

	CollisionDetect::toShiftDirect _to = getToShift(_isAction, nowStatus);
	
	// 条件の見直しが必要！！（2020/04/26）
	if (getSwitchAction(_isAction) &&
		_isAction != Define::rollAction_Basic::Fall &&
		_isAction != Define::rollAction_Basic::Idle &&
		_isAction != Define::rollAction_Basic::Run &&
		_isAction != Define::rollAction_Basic::Walk)
		pysicQty.refreshVel(true, false);

	// 次のコマで、y方向にその速度で動いて大丈夫か？もし障壁があったら、、、
	bool cannotShift = _collision->calcShitingCollisionedSideVertical(_to, std::abs(pysicQty.y_vel));
	bool isCollision = !getForwardCollisionedSide(_to, _collision);
	if (cannotShift && isCollision)
	{
		//bottom辺の一番近いブロック上のブロックの下辺座標に移動する。
		int x = nowStatus._x;
		int Forward_Block_nearSideY = getForwardBlockNearSide(nowStatus, _to, pysicQty, _collision, _stage);
		int y = Forward_Block_nearSideY + getRangeOfNearBlock(_to, pysicQty, _collision);
		_collision->update(pysicQty.setPoint(nowStatus, x, y), _stage);
		pysicQty.refreshVel(true, false);
		return pysicQty.setPoint(nowStatus, x, y);
	}

	// 速度の方向に障壁が何もなかったらpysicQtyの更新を行う。
	
	// _toの方向に何もない、かつ、_toの方向に座標が移動しているなら更新
	bool forwardCollision = !getForwardCollisionedSide(_to, _collision);
	bool pysicShifting = pysicQty.getShifting(_to, _isAction);
	if (forwardCollision && pysicShifting) {
		return pysicQty.update(
				nowStatus,
				getAcc(nowStatus, _isAction, pysicQty)[0],
				getAcc(nowStatus, _isAction, pysicQty)[1], 
				_isInitFroce[static_cast<int>(_isAction)],
				getUptoVelHorizon(nowStatus, _isAction),
				0,
				_validGravityAction[static_cast<int>(_isAction)],
				_validStoppingAction[static_cast<int>(_isAction)]
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
		return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to) + _collision->collisionSideRange.bottom).y1;
		break;
	case CollisionDetect::toShiftDirect::_vertical://垂直だったら座標がどっちに動いているかで判断（速度０はどっちでも構わないが上に合わせる）
		if(_pysic.y_vel <= 0)
			return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to, _pysic.y_vel) - Define::blockHeight).y2;
		else
			return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to, _pysic.y_vel) + Define::blockHeight).y1;
	case CollisionDetect::toShiftDirect::_none://停止状態であるべき時は下のブロックに合わせる
		return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to)).y1;

	}
	return 0;
}

//  _isActionの状態でどの方向に動くアクションなのかを計算する。
CollisionDetect::toShiftDirect AnimationMove::getToShift(Define::rollAction_Basic _isAction, Define::Status nowStatus)
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
		if (nowStatus.directRight)
			return CollisionDetect::toShiftDirect::right;
		else
			return CollisionDetect::toShiftDirect::left;
		break;
	case Define::rollAction_Basic::Walk:
		if (nowStatus.directRight)
			return CollisionDetect::toShiftDirect::right;
		else
			return CollisionDetect::toShiftDirect::left;
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
	case CollisionDetect::toShiftDirect::_none:
		return -_collision->getRange(CollisionDetect::toShiftDirect::bottom);
		break;
	}
	return 0;
}

std::vector<char> AnimationMove::getAcc(Define::Status nowStatus, Define::rollAction_Basic _isAction, PysicalQTY _pysic)
{
	std::vector<char> retPoint(2, 0);
	switch (_isAction) {
	case Define::rollAction_Basic::Jump_MidAir:
		break;
	case Define::rollAction_Basic::Jump_Up:
		break;
	case Define::rollAction_Basic::Fall:
		break;
	case Define::rollAction_Basic::Walk:
		if (nowStatus.directRight)
			retPoint[0] = 1;
		else
			retPoint[0] = -1;
		break;
	case Define::rollAction_Basic::Run:
		if (nowStatus.directRight)
			retPoint[0] = 1;
		else
			retPoint[0] = -1;
		break;
	case Define::rollAction_Basic::Idle:
		if (nowStatus.directRight && pysicQty.x_vel > 0)
			retPoint[0] = -1;
		else if(!nowStatus.directRight && pysicQty.x_vel < 0)
			retPoint[0] = 1;
		break;
	}
	return retPoint;
}

char AnimationMove::getUptoVelHorizon(Define::Status nowStatus, Define::rollAction_Basic _isAction)
{
	switch (_isAction) {
	case Define::rollAction_Basic::Walk:
		if (nowStatus.directRight)
			return uptoVel_walk;
		else
			return -uptoVel_walk;
		break;
	case Define::rollAction_Basic::Run:
		if (nowStatus.directRight)
			return uptoVel_run;
		else
			return -uptoVel_run;
		break;
	case Define::rollAction_Basic::Idle:
		if (nowStatus.directRight)
			return 0;
		else
			return 0;
		break;
	}

	return 0;
}