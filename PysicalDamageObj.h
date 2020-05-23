#pragma once
#include "Pysical.h"
class PysicalDamageObj :
	public Pysical
{
	int initVelX;
	int initVelY;
	bool _isDireRight;

	// 重力はNコマに一回有効
	unsigned char validGravityN = 6;
	unsigned char validGravityCounter = 0;


	Dimention affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight);

	//! affectGravity（対象の加速度）に対し、重力を加える。
	Dimention affectGravity(Dimention affectedAcc, characterAction nowAction) override;

public:
	PysicalDamageObj(int _initVelX, int _initVelY, bool __isDireRight) {
		initVelX = _initVelX;
		initVelY = _initVelY;
		_isDireRight = __isDireRight;
	}
	~PysicalDamageObj() = default;

	//! アクション状態とその方向により速度と加速度を更新し、速度を返す。
	Dimention update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> _collision, VirtualController controller);

};

