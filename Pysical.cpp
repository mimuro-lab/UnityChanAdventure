#include "Pysical.h"

Dimention Pysical::affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned char nowTime)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0) {
		returnVel.x += _isInitVelocity[static_cast<int>(nowAction)].x;
		returnVel.y += _isInitVelocity[static_cast<int>(nowAction)].y;
	}

	return returnVel;
}

Dimention Pysical::affectGravity(Dimention affectedAcc, rollAction_Basic nowAction)
{
	Dimention returnAcc = affectedAcc;

	if(_validGravityAction[static_cast<int>(nowAction)])
		returnAcc.y += acc_gravity;

	return returnAcc;

}

Dimention Pysical::affectBraking(Dimention affectedAcc, rollAction_Basic nowAction)
{
	Dimention returnAcc = affectedAcc;

	if (_validBrakingAction[static_cast<int>(nowAction)])
		returnAcc.y += acc_brake;

	return returnAcc;
}

Dimention Pysical::getForceFromAction(rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnForce;

	returnForce.x = returnForce.y = 0;

	switch (nowAction) {
	case rollAction_Basic::Brake:
		if (isDireRight)
			returnForce.x = -acc_brake;
		else
			returnForce.x = acc_brake;
		break;
	case rollAction_Basic::Idle:
		if (isDireRight)
			returnForce.x = -acc_brake;
		else
			returnForce.x = acc_brake;
		break;
	case rollAction_Basic::Walk:
		if (isDireRight)
			returnForce.x = acc_walk;
		else
			returnForce.x = -acc_walk;
		break;
	case rollAction_Basic::Run:
		if (isDireRight)
			returnForce.x = acc_run;
		else
			returnForce.x = -acc_run;
		break;
	}

	return returnForce;
}

Dimention Pysical::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc)
{
	Dimention returnVelocity = affectedVel;

	returnVelocity.x += affectAcc.x;
	returnVelocity.y += affectAcc.y;

	return returnVelocity;
}

Dimention Pysical::matchingVelAndDireHorizon(Dimention affectedVel, bool isDireRight)
{
	Dimention returnVel = affectedVel;

	// 右を向いて、速度が０より小さいなら速度を０にする。
	if (isDireRight && returnVel.x < 0) 
		returnVel.x = 0;
	// 左を向いて、速度が０より大きいなら速度を０にする。
	if (!isDireRight && returnVel.x > 0)
		returnVel.x = 0;

	return returnVel;
}

Dimention Pysical::update(rollAction_Basic nowAction, bool isDireRight)
{

	// Actionが切り替わったら時間を０にする。
	if (isSwitching(nowAction))
		time = 0;

	// 初速度を有効にする。
	now_vel = affectInitVelocity(now_vel, nowAction, time);

	// 加速度を計算する。
	now_acc = getForceFromAction(nowAction, isDireRight);
	now_acc = affectGravity(now_acc, nowAction);
	now_acc = affectBraking(now_acc, nowAction);

	// 加速度から速度を更新する。
	now_vel = calcVelocityFromAccel(now_vel, now_acc);

	// 向いている方向と水平方向の速度方向の調和をとる。
	now_vel = matchingVelAndDireHorizon(now_vel, isDireRight);

	time++;

	return now_vel;
}