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


	if (_isAction == Define::rollAction_Basic::Fall) {
		_nextStatus._y++;
		_nextStatus._y_speed = 1;
	}


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
	bool cannotShiftVertical = _collision->calcShitingCollisionedSideVertical(_to, std::abs(pysicQty.y_vel));//_rangeはとりあえず絶対値を渡す（エラー:2020/04/27）
	bool cannotShiftHorizon = _collision->calcShitingCollisionedSideHorizon(_to, pysicQty.x_vel);
	bool isCollision = !getForwardCollisionedSide(_to, _collision);
	if (isCollision)
	{
		// 垂直方向に動くことができないなら
		if (cannotShiftVertical) {
			//bottom辺の一番近いブロック上のブロックの下辺座標に移動する。
			int x = nowStatus._x;
			int Forward_Block_nearSideY = getForwardBlockNearSideVertical(nowStatus, _to, pysicQty, _collision, _stage);
			int y = Forward_Block_nearSideY + getRangeOfNearBlock(_to, pysicQty, _collision);
			_collision->update(pysicQty.setPoint(nowStatus, pysicQty, x, y), _stage);
			pysicQty.refreshVel(true, false);
			return pysicQty.setPoint(nowStatus, pysicQty, x, y);
		}
		// 水平方向に動くことができないなら
		if (cannotShiftHorizon && _isAction != Define::rollAction_Basic::Idle) {
			//bottom辺の一番近いブロック上のブロックの下辺座標に移動する。
			//int x = nowStatus._x;
			//int Forward_Block_nearSideY = getForwardBlockNearSide(nowStatus, _to, pysicQty, _collision, _stage);
			//int y = Forward_Block_nearSideY + getRangeOfNearBlock(_to, pysicQty, _collision);
			int y = nowStatus._y;
			int Forward_Block_nearSide = getForwardBlockNearSideHorizon(nowStatus, _to, pysicQty, _collision, _stage);
			int x = Forward_Block_nearSide + getRangeOfNearBlockHorizon(_to, pysicQty, _collision);
			_collision->update(pysicQty.setPoint(nowStatus, pysicQty, x, y), _stage);
			pysicQty.refreshVel(false, true);
			return pysicQty.setPoint(nowStatus, pysicQty, x, y);
		}

		//pysicQty.refreshVel(true, true, true);
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

int AnimationMove::getForwardBlockNearSideVertical(
	Define::Status nowStatus, 
	CollisionDetect::toShiftDirect _to, 
	PysicalQTY _pysic,
	std::shared_ptr<CollisionDetect> _collision, 
	std::shared_ptr<Stage> _stage
)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head:
		return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) - Define::blockHeight).y2;
		break;
	case CollisionDetect::toShiftDirect::bottom:
		return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) + _collision->collisionSideRange.bottom).y1;
		break;
	case CollisionDetect::toShiftDirect::_vertical://垂直だったら座標がどっちに動いているかで判断（速度０はどっちでも構わないが上に合わせる）
		if(_pysic.y_vel <= 0)
			return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) - Define::blockHeight).y2;
		else
			return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) + Define::blockHeight).y1;

	case CollisionDetect::toShiftDirect::_none://停止状態であるべき時は下のブロックに合わせる
		return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel)).y1;

	}
	return 0;
}
int AnimationMove::getForwardBlockNearSideHorizon(
	Define::Status nowStatus,
	CollisionDetect::toShiftDirect _to,
	PysicalQTY _pysic,
	std::shared_ptr<CollisionDetect> _collision,
	std::shared_ptr<Stage> _stage
)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::right:
		return _stage->getBlockCell(nowStatus._x + _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) + Define::blockWidth, nowStatus._y).x1;
		break;

	case CollisionDetect::toShiftDirect::left:
		return _stage->getBlockCell(nowStatus._x - _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) - Define::blockWidth, nowStatus._y).x2;
		break;

	case CollisionDetect::toShiftDirect::_holizen:
		if (_pysic.x_vel <= 0)
			return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) - Define::blockHeight).y2;
		else
		return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to, _pysic.x_vel, _pysic.y_vel) + Define::blockHeight).y1;

	case CollisionDetect::toShiftDirect::_none://停止状態であるべき時は左のブロックに合わせる
		DrawLine(nowStatus._x - _collision->getRange(CollisionDetect::toShiftDirect::left, _pysic.x_vel, _pysic.y_vel) - Define::blockWidth, 0,
			nowStatus._x - _collision->getRange(CollisionDetect::toShiftDirect::left, _pysic.x_vel, _pysic.y_vel) - Define::blockWidth, 500, GetColor(255, 0, 0));
		
		int x = nowStatus._x - _collision->getRange(CollisionDetect::toShiftDirect::left, _pysic.x_vel, _pysic.y_vel) - Define::blockWidth;

		int y = nowStatus._y;

		return _stage->getBlockCell(x, y).x2;

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

// プレイヤーオブジェクトの中心座標からプレイヤーオブジェクトの当たり判定までの距離 toHeadとかtoRight
int AnimationMove::getRangeOfNearBlock(CollisionDetect::toShiftDirect _to, PysicalQTY _pysic, std::shared_ptr<CollisionDetect> _collision)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head://上のレンガに合わせられるので下向き。
		return _collision->getRange(CollisionDetect::toShiftDirect::head, 0, 0);
		break;
	case CollisionDetect::toShiftDirect::bottom://下のレンガに合わせられるので上向き。
		return -_collision->getRange(CollisionDetect::toShiftDirect::bottom, 0, 0);
		break;
	case CollisionDetect::toShiftDirect::_vertical://垂直だったら座標がどっちに動いているかで判断（速度０はどっちでも構わないが上に合わせる）
		if (_pysic.y_vel <= 0)
			return _collision->getRange(CollisionDetect::toShiftDirect::head, 0, 0);
		else
			return -_collision->getRange(CollisionDetect::toShiftDirect::bottom, 0, 0);
		break;

	case CollisionDetect::toShiftDirect::right://上のレンガに合わせられるので下向き。
		return _collision->getRange(CollisionDetect::toShiftDirect::right, 0, 0);
		break;
	case CollisionDetect::toShiftDirect::left://上のレンガに合わせられるので下向き。
		return _collision->getRange(CollisionDetect::toShiftDirect::left, 0, 0);
		break;
	case CollisionDetect::toShiftDirect::_holizen:
		if(_pysic.x_vel <= 0)
			return _collision->getRange(CollisionDetect::toShiftDirect::left, 0, 0);
		else
			return _collision->getRange(CollisionDetect::toShiftDirect::right, 0, 0);

	case CollisionDetect::toShiftDirect::_none:
		return -_collision->getRange(CollisionDetect::toShiftDirect::bottom, 0, 0);
		break;
	}
	return 0;
}

// プレイヤーオブジェクトの中心座標からプレイヤーオブジェクトの当たり判定までの距離 toHeadとかtoRight
int AnimationMove::getRangeOfNearBlockHorizon(CollisionDetect::toShiftDirect _to, PysicalQTY _pysic, std::shared_ptr<CollisionDetect> _collision)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::right://上のレンガに合わせられるので下向き。
		return _collision->getRange(CollisionDetect::toShiftDirect::right, 0, 0);
		break;
	case CollisionDetect::toShiftDirect::left://上のレンガに合わせられるので下向き。
		return _collision->getRange(CollisionDetect::toShiftDirect::left, 0, 0);
		break;
	case CollisionDetect::toShiftDirect::_holizen:
		if (_pysic.x_vel <= 0)
			return _collision->getRange(CollisionDetect::toShiftDirect::left, 0, 0);
		else
			return _collision->getRange(CollisionDetect::toShiftDirect::right, 0, 0);

	case CollisionDetect::toShiftDirect::_none:
		return _collision->getRange(CollisionDetect::toShiftDirect::left, 0, 0);
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