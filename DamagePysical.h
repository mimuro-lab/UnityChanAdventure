#pragma once
#include "Define.h"

using namespace Define;

class DamagePysical
{

	unsigned char gravity = Accel_gravity;

	Dimention velocity;

	Dimention accel;

	//! affectGravity（対象の加速度）に対し、重力を加える。
	Dimention affectGravity(Dimention affectedAcc) {
		Dimention nextAcc = affectedAcc;
		nextAcc.y += gravity;
		return nextAcc;
	}

	//! 加速度から速度を計算する。
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc);

	//! 速度から位置を計算する。
	Dimention calcPointFromVelocity(Dimention affectPoint, Dimention affectVel);

public:
	DamagePysical() {
		velocity.x = velocity.y = 0;
		accel.x = accel.y = 0;
	}
	~DamagePysical() = default;

	Dimention update(Dimention nowPoint);

};

