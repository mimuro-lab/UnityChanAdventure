#include "PysicalBullet.h"


/*!
@brief Action状態から、その時の速度の限界値を得る。方向も考慮しており、扱うのは速度が前提。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalBullet::getLimitVelFromAction(characterAction nowAction, bool isDireRight, VirtualController controller)
{
	Dimention returnVelocity;

	returnVelocity.x = returnVelocity.y = 128;

	// 歩く・走るの時は常に空中の速度の上限を代入し続ける。
	if (nowAction == characterAction::Run || nowAction == characterAction::Walk) {
		if (isDireRight) {
			limVel_inAir_jumpUp = std::abs(now_vel.x);
			if (std::abs(now_vel.x) < limVel_walk)
				limVel_inAir_jumpUp = std::abs(limVel_walk);
		}
		else {
			limVel_inAir_jumpUp = -std::abs(now_vel.x);
			if (std::abs(now_vel.x) < limVel_walk)
				limVel_inAir_jumpUp = -std::abs(limVel_walk);
		}
		if (now_vel.x == 0) {
			if (isDireRight)
				limVel_inAir_jumpUp = limVel_walk;
			else
				limVel_inAir_jumpUp = -limVel_walk;
		}
	}
	if (nowAction == characterAction::Idle) {
		if (isDireRight)
			limVel_inAir_jumpUp = limVel_walk;
		else
			limVel_inAir_jumpUp = -limVel_walk;
	}

	if (preAction == characterAction::Walk || preAction == characterAction::Run)
		limVel_inAir = limVel_inAir_jumpUp;

	// 空中で方向転換したかどうか。
	//if (nowAction == characterAction::Jump_Up || nowAction == characterAction::Jump_MidAir ||
	//	nowAction == characterAction::Jump_Fall || nowAction == characterAction::Fall) {
	//	preJumpingDireRight = isDireRight;

		//if (preJumpingDireRight != nowJumpingDireRight) 
		{
			if (isDireRight) {
				limVel_inAir = 128;
			}
			if (!isDireRight) {
				limVel_inAir = -128;
			}
		}

	//	nowJumpingDireRight = preJumpingDireRight;
	//}

	nowJumpingDireRight = preJumpingDireRight = isDireRight;

	switch (nowAction) {
	case characterAction::Walk:
		if (isDireRight)
			returnVelocity.x = limVel_walk;
		else
			returnVelocity.x = -limVel_walk;
		break;
	case characterAction::Run:
		if (isDireRight)
			returnVelocity.x = limVel_run;
		else
			returnVelocity.x = -limVel_run;
		break;

	case characterAction::Jump_Up:
		returnVelocity.x = limVel_inAir;
		break;
	case characterAction::Jump_MidAir:
		returnVelocity.x = limVel_inAir;
		break;
	case characterAction::Fall:
		returnVelocity.x = limVel_inAir;
		break;

	}

	//DrawFormatString(100, 20, GetColor(255, 255, 255), "vel_lim x:%d, y:%d", returnVelocity.x, returnVelocity.y);

	preAction = nowAction;

	return returnVelocity;
}

/*!
@brief 摩擦力を有効にする関数。扱うのは加速度が前提。
@date 2020/05/04/19:19
@author mimuro
*/
Dimention PysicalBullet::affectFriction(Dimention affectedAcc, Dimention nowVelocity, characterAction nowAction, bool isDireRight)
{
	Dimention returnAcc = affectedAcc;

	if (nowAction == characterAction::Jump_Up ||
		nowAction == characterAction::Jump_MidAir ||
		nowAction == characterAction::Jump_Fall ||
		nowAction == characterAction::Fall) {
		if (now_vel.x == 0)
			return returnAcc;
	}

	if (_validFrictionAction[static_cast<int>(nowAction)] && nowAction != characterAction::Fall) {
		if (isDireRight) {
			returnAcc.x -= acc_friction;
		}
		if (!isDireRight) {
			returnAcc.x += acc_friction;
		}
	}
	
	if (nowAction == characterAction::Fall) {
		if (isDireRight && now_vel.x > minVel_inAir) {
			returnAcc.x -= acc_friction;
		}
		if (!isDireRight && now_vel.x < -minVel_inAir) {
			returnAcc.x += acc_friction;
		}
	}

	return returnAcc;
}

/*!
@brief その時の加速度から、次の速度を計算する。返すのは速度。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalBullet::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, characterAction nowAction, bool isDireRight, VirtualController controller)
{
	Dimention returnVelocity = affectedVel;

	int limitX = std::abs(getLimitVelFromAction(nowAction, isDireRight, controller).x);
	int nextVelAbs = std::abs(returnVelocity.x + affectAcc.x);

	// 更新後の速度が限界値を超えないようであれば速度に加速度を足す
	if (nextVelAbs <= limitX) {
		returnVelocity.x += affectAcc.x;
	}
	// 超えるようであれば限界値に設定する。(向きによって)
	else
		returnVelocity.x = getLimitVelFromAction(nowAction, isDireRight, controller).x;

	returnVelocity.y += affectAcc.y;

	return returnVelocity;
}


Dimention PysicalBullet::affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0 && !collision->getCollisionedSide().bottom) {
		if (isDireRight)
			returnVel.x += std::abs(initVelX);
		else {
			returnVel.x -= std::abs(initVelX);
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
		timeInAction = 0;

	// 初速度を有効にする。
	now_vel = affectInitVelocity(now_vel, nowAction, timeFromBorn, collision, _isDireRight);

	// 加速度を計算する。
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight, controller);
		now_acc = affectGravity(now_acc, nowAction);
		now_acc = affectFriction(now_acc, now_vel, nowAction, isDireRight);
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
