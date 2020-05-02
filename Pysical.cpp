#include "Pysical.h"

Define::Status Pysical::update(
	Define::Status _nowStatus, 
	char _x_acc, char _y_acc, 
	char _initialForceY, 
	char _x_vel_upto, char _y_vel_upto, 
	bool _validGravity, bool _validStopping)
{

	Define::Status nextStatus = _nowStatus;

	x_acc = _x_acc;

	if (_validGravity)
		y_acc = _y_acc + acc_gravity;
	else
		y_acc = y_acc;

	if (time == 0) {
		y_vel += _initialForceY;
	}

	if (_x_vel_upto > 0) {
		if (_x_vel_upto >= x_vel + x_acc)
			x_vel += x_acc;
		else if (x_vel + x_acc > _x_vel_upto)
			x_vel = _x_vel_upto;
	}
	else if (_x_vel_upto < 0) {
		if (_x_vel_upto <= x_vel + x_acc)
			x_vel += x_acc;
		else if (x_vel + x_acc < _x_vel_upto)
			x_vel = _x_vel_upto;
	}

	// _validStoppingはnowStatusの速度方向とオブジェクト向きが等しいときのみ有効。
	if (_validStopping)
	{
		//右方向に進んでいたら
		if (x_vel > 0) {
			if (_x_vel_upto <= x_vel + x_acc)
				x_vel += x_acc;
			else if (x_vel + x_acc < _x_vel_upto)
				x_vel = _x_vel_upto;
		}
		//左方向に進んでいたら
		if (x_vel < 0) {
			if (_x_vel_upto >= x_vel + x_acc)
				x_vel += x_acc;
			else if (x_vel + x_acc > _x_vel_upto)
				x_vel = _x_vel_upto;
		}
	}
	//速度方向とオブジェクト向きが異なるときは強制的に水平方向の速度・加速度をゼロにする。

	y_vel += y_acc;

	nextStatus._x += x_vel;
	nextStatus._y += y_vel;

	nextStatus._x_speed = x_vel;
	nextStatus._y_speed = y_vel;

	time++;

	return nextStatus;
}

Define::Status Pysical::setPoint(Define::Status _nowStatus, Pysical _pysic, int x, int y)
{
	time++;
	Define::Status nextStatus = _nowStatus;
	nextStatus._x = x;
	nextStatus._y = y;
	nextStatus._x_speed = _pysic.x_vel;
	nextStatus._y_speed = _pysic.y_vel;
	return nextStatus;
}

bool Pysical::getShifting(CollisionDetect::toShiftDirect dire, Define::rollAction_Basic _isAction)
{

	if (_isAction == Define::rollAction_Basic::Idle)
		return true;

	switch (dire) {
	case CollisionDetect::toShiftDirect::head:
		if (y_vel < 0) return true;
		if (y_vel > 0) return false;
		break;
	case CollisionDetect::toShiftDirect::bottom:
		if (y_vel > 0) return true;
		if (y_vel < 0) return false;
		break;
	case CollisionDetect::toShiftDirect::right:
		if (x_vel > 0) return true;
		if (x_vel < 0) return false;
		break;
	case CollisionDetect::toShiftDirect::left:
		if (x_vel < 0) return true;
		if (x_vel > 0) return false;
		break;
	case CollisionDetect::toShiftDirect::_vertical://垂直に動くべきだったらyの速度方向は関係ない。つまり必ずtrueを返す
		return true;
	}

	switch (dire) {
	case CollisionDetect::toShiftDirect::head:
		if (_isAction == Define::rollAction_Basic::Jump_Up ||
			_isAction == Define::rollAction_Basic::Jump_MidAir)
			return true;
		break;
	case CollisionDetect::toShiftDirect::bottom:
		if (_isAction == Define::rollAction_Basic::Fall ||
			_isAction == Define::rollAction_Basic::Jump_Fall ||
			_isAction == Define::rollAction_Basic::Jump_MidAir)
			return true;
		break;
	case CollisionDetect::toShiftDirect::right:
		if (_isAction == Define::rollAction_Basic::Walk ||
			_isAction == Define::rollAction_Basic::Run)
			return true;
		break;
	case CollisionDetect::toShiftDirect::left:
		if (_isAction == Define::rollAction_Basic::Walk ||
			_isAction == Define::rollAction_Basic::Run)
			return true;
		break;
	}

	return false;
}

void Pysical::refreshVel(bool vertical, bool horizon, bool _time) {
	if (vertical)	y_vel = y_acc = 0;
	if (horizon)		x_vel = x_acc = 0;
	if (_time)	time = 0;
}