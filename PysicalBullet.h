#pragma once
#include "Pysical.h"
class PysicalBullet :
	public Pysical
{
	int initVelX;
	int initVelY;
	bool _isDireRight;

	// 重力はNコマに一回有効
	unsigned char validGravityN = 6;
	unsigned char validGravityCounter = 0;

	// 空中の最小速度
	unsigned char minVel_inAir = 5;

	//! アクション状態とその方向から速度の限界値を得る。
	Dimention getLimitVelFromAction(characterAction nowAction, bool isDireRight, VirtualController controller) override;

	//! 加速度から速度を計算する。
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, characterAction nowAction, bool isDireRight, VirtualController controller) override;

	Dimention affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight);

	//! affectGravity（対象の加速度）に対し、重力を加える。
	Dimention affectGravity(Dimention affectedAcc, characterAction nowAction) override;

	//! affectGravity（対象の加速度）に対し、さらに地面との摩擦を加える。
	Dimention affectFriction(Dimention affectedAcc, Dimention nowVelocity, characterAction nowAction, bool isDireRight);

public:
	PysicalBullet(int _initVelX, int _initVelY, bool __isDireRight) {
		initVelX = _initVelX;
		initVelY = _initVelY;
		_isDireRight = __isDireRight;
	}
	~PysicalBullet() = default;

	//! アクション状態とその方向により速度と加速度を更新し、速度を返す。
	Dimention update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> _collision, VirtualController controller);



};

