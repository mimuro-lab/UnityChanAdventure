#include "PysicalSword.h"

/*!
@brief 現在のアクション状態から速度を計算し、返す。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalSword::update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> collision, VirtualController controller)
{

	// Actionが切り替わったら時間を０にする。
	if (isSwitching(nowAction))
		timeInAction = 0;

	// 加速度を計算する。
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight, controller);
		//now_acc = affectGravity(now_acc, nowAction);
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

	timeInAction++;
	timeFromBorn++;
	//DrawFormatString(100, 70, GetColor(255, 255, 255), "now acc x:%d, y:%d", now_acc.x, now_acc.y);
	return now_vel;
}
