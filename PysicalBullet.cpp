#include "PysicalBullet.h"

Dimention PysicalBullet::affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0 && !collision->getCollisionedSide().bottom) {
		if (isDireRight)
			returnVel.x += std::abs(initVelX);
		else {
			returnVel.x -= std::abs(initVelX + limVel_walk)				;
		}
		returnVel.y += initVelY;
	}

	return returnVel;
}

/*!
@brief 重力を有効にする関数。扱うのは加速度が前提。
@date 2020/05/04/19:19
@author mimuro
*/
Dimention PysicalBullet::affectGravity(Dimention affectedAcc, characterAction nowAction)
{
	Dimention returnAcc = affectedAcc;

	if (_validGravityAction[static_cast<int>(nowAction)]) {
		validGravityCounter++;
		validGravityCounter %= validGravityN;
		if(validGravityCounter==0)
			returnAcc.y += acc_gravity;
	}

	return returnAcc;

}



/*!
@brief 現在のアクション状態から速度を計算し、返す。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalBullet::update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> collision, VirtualController controller)
{

	// Actionが切り替わったら時間を０にする。
	if (isSwitching(nowAction))
		time = 0;

	// 初速度を有効にする。
	now_vel = affectInitVelocity(now_vel, nowAction, time, collision, _isDireRight);

	// 加速度を計算する。
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight, controller);
		now_acc = affectGravity(now_acc, nowAction);
		now_acc = affectFriction(now_acc, nowAction, isDireRight);
	}
	else {
		now_acc.x = now_acc.y = 0;
	}
	addAccCounter++;
	addAccCounter %= addAccN;

	// 加速度から速度を更新する。
	now_vel = calcVelocityFromAccel(now_vel, now_acc, nowAction, isDireRight, controller);

	// 向いている方向と水平方向の速度方向の調和をとる。
	now_vel = matchingVelAndDireHorizon(now_vel, nowAction, isDireRight);

	time++;
	//DrawFormatString(100, 70, GetColor(255, 255, 255), "now acc x:%d, y:%d", now_acc.x, now_acc.y);
	return now_vel;
}
