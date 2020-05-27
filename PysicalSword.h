#pragma once
#include "Pysical.h"

class PysicalSword :
	public Pysical
{
	int initVelX;
	int initVelY;
	bool _isDireRight;

public:
	PysicalSword(int _initVelX, int _initVelY, bool __isDireRight) {
		initVelX = _initVelX;
		initVelY = _initVelY;
		_isDireRight = __isDireRight;
	}
	~PysicalSword() = default;

	//! アクション状態とその方向により速度と加速度を更新し、速度を返す。
	Dimention update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> _collision, VirtualController controller);

};

