
/*!
@file Pysical.cpp
@brief Pysicalクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/05/04/19:17
@author mimuro
*/

#include "Pysical.h"

/*!
@brief 初速度を有効にする。nowTimeが0の時のみ速度に対し、初速度を与える。扱うのは速度が前提。
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned char nowTime)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0) {
		returnVel.x += _isInitVelocity[static_cast<int>(nowAction)].x;
		returnVel.y += _isInitVelocity[static_cast<int>(nowAction)].y;
	}

	return returnVel;
}

/*!
@brief 重力を有効にする関数。扱うのは加速度が前提。
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::affectGravity(Dimention affectedAcc, rollAction_Basic nowAction)
{
	Dimention returnAcc = affectedAcc;

	if(_validGravityAction[static_cast<int>(nowAction)])
		returnAcc.y += acc_gravity;

	return returnAcc;

}

/*!
@brief 摩擦力を有効にする関数。扱うのは加速度が前提。
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::affectFriction(Dimention affectedAcc, rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnAcc = affectedAcc;

	if (_validFrictionAction[static_cast<int>(nowAction)]) {
		if (isDireRight)
			returnAcc.x -= acc_friction;
		if (!isDireRight)
			returnAcc.x += acc_friction;
	}

	return returnAcc;
}

/*!
@brief Action状態から、その時の加速度を得る。
@date 2020/05/04/19:19
@author mimuro
*/
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

/*!
@brief Action状態から、その時の速度の限界値を得る。方向も考慮しており、扱うのは速度が前提。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::getLimitVelFromAction(rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnVelocity;

	returnVelocity.x = returnVelocity.y = 128;

	switch (nowAction) {
	case rollAction_Basic::Walk:
		if(isDireRight)
			returnVelocity.x = limVel_walk;
		else
			returnVelocity.x = -limVel_walk;
		break;
	case rollAction_Basic::Run:
		if (isDireRight)
			returnVelocity.x = limVel_run;
		else
			returnVelocity.x = -limVel_run;
		break;
	}

	return returnVelocity;
}

/*!
@brief その時の加速度から、次の速度を計算する。返すのは速度。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnVelocity = affectedVel;
	
	int limitX = std::abs(getLimitVelFromAction(nowAction, isDireRight).x);
	int nextVelAbs = std::abs(returnVelocity.x + affectAcc.x);

	// 更新後の速度が限界値を超えないようであれば速度に加速度を足す
	if (nextVelAbs <= limitX) {
		returnVelocity.x += affectAcc.x;
	}
	// 超えるようであれば限界値に設定する。(向きによって)
	else
		returnVelocity.x = getLimitVelFromAction(nowAction, isDireRight).x;

	returnVelocity.y += affectAcc.y;

	return returnVelocity;
}

/*!
@brief 速度と向く方向が異なるとき（例えばBrake）に、加速度が逆方向にかかりすぎないように制御する関数。返すのは速度。
@date 2020/05/04/19:26
@author mimuro
*/
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

/*!
@brief 現在のアクション状態から速度を計算し、返す。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::update(rollAction_Basic nowAction, bool isDireRight)
{

	// Actionが切り替わったら時間を０にする。
	if (isSwitching(nowAction))
		time = 0;

	// 初速度を有効にする。
	now_vel = affectInitVelocity(now_vel, nowAction, time);

	// 加速度を計算する。
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight);
		now_acc = affectGravity(now_acc, nowAction);
		now_acc = affectFriction(now_acc, nowAction, isDireRight);
	}
	else {
		now_acc.x = now_acc.y = 0;
	}
	addAccCounter++;
	addAccCounter %= addAccN;

	// 加速度から速度を更新する。
	now_vel = calcVelocityFromAccel(now_vel, now_acc, nowAction, isDireRight);

	// 向いている方向と水平方向の速度方向の調和をとる。
	now_vel = matchingVelAndDireHorizon(now_vel, isDireRight);

	time++;

	return now_vel;
}

/*!
@brief 障壁にぶつかった時に速度をリセットする関数。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::resetByCollision(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision)
{

	Dimention retVec = resetedVector;

	// 速度が０の時はいじらない。

	/// y速度の処理
	// 速度が下向き、かつ、下側が衝突しているならy速度をリセット
	if (resetedVector.y > 0 && _collision->getCollisionedSide().bottom)
		retVec.y = 0;

	// 速度が上向き、かつ、上側が衝突しているならy速度をリセット(速度が0を含めるのは、ジャンプした時にリセットする為)
	if (resetedVector.y <= 0 && _collision->getCollisionedSide().head)
		retVec.y = 0;

	/// x速度の処理
	// 速度が右向き、かつ、右側が衝突しているならx速度をリセット
	if (resetedVector.x > 0 && _collision->getCollisionedSide().right)
		retVec.x = 0;

	// 速度が左向き、かつ、左側が衝突しているならx速度をリセット
	if (resetedVector.x < 0 && _collision->getCollisionedSide().left)
		retVec.x = 0;

	return retVec;
}

/*!
@brief 速度を適切なリセット処理する。
@date 2020/05/04/19:34
@author mimuro
*/
Dimention Pysical::resetVelocity(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision)
{
	Dimention retVec = resetedVector;

	retVec = resetByCollision(retVec, _collision);

	now_vel = retVec;

	return retVec;

}