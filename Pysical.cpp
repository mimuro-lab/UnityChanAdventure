
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
Dimention Pysical::affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, VirtualController controller)
{
	Dimention returnVel = affectedVel;


	if (nowTime == 0) {
		returnVel.x += _isInitVelocity[static_cast<int>(nowAction)].x;
		if (nowAction == characterAction::Jump_MidAir) {
			if (controller.on_A) {
				returnVel.y += _isInitVelocity[static_cast<int>(nowAction)].y;
			}
		}
		else {
			returnVel.y += _isInitVelocity[static_cast<int>(nowAction)].y;
		}
		
	}

	bool jump_continue = (nowAction == characterAction::Jump_Up) && (controller.on_A);

	if (jump_continue) {
		returnVel.y = _isInitVelocity[static_cast<int>(nowAction)].y;
	}
	return returnVel;
}

/*!
@brief 重力を有効にする関数。扱うのは加速度が前提。
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::affectGravity(Dimention affectedAcc, characterAction nowAction)
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
Dimention Pysical::affectFriction(Dimention affectedAcc, characterAction nowAction, bool isDireRight)
{
	Dimention returnAcc = affectedAcc;

	if (nowAction == characterAction::Jump_Up ||
		nowAction == characterAction::Jump_MidAir ||
		nowAction == characterAction::Jump_Fall ||
		nowAction == characterAction::Fall) {
		if (now_vel.x == 0)
			return returnAcc;
	}
	
	if (_validFrictionAction[static_cast<int>(nowAction)]) {
		
		if (isDireRight) {
			returnAcc.x -= acc_friction;
		}
		if (!isDireRight) {
			returnAcc.x += acc_friction;
		}
		
	}

	return returnAcc;
}

/*!
@brief Action状態から、その時の加速度を得る。
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::getForceFromAction(characterAction nowAction, bool isDireRight, VirtualController controller)
{
	Dimention returnForce;

	returnForce.x = returnForce.y = 0;

	bool inputtingRight = controller.on_right;
	bool inputtingLeft = controller.on_left;

	switch (nowAction) {
	case characterAction::Brake:
		if (isDireRight)
			returnForce.x = -acc_brake;
		else
			returnForce.x = acc_brake;
		break;
	case characterAction::Walk:
		if (isDireRight)
			returnForce.x = acc_walk;
		else
			returnForce.x = -acc_walk;
		break;
	case characterAction::Run:
		if (isDireRight)
			returnForce.x = acc_run;
		else
			returnForce.x = -acc_run;
		break;
		
	case characterAction::Jump_Up:
		if (inputtingRight)
			returnForce.x = acc_inAir;
		else if(inputtingLeft)
			returnForce.x = -acc_inAir;
		break;
	case characterAction::Jump_MidAir:
		if (inputtingRight)
			returnForce.x = acc_inAir;
		else if (inputtingLeft)
			returnForce.x = -acc_inAir;
		break;
	case characterAction::Fall:
		if (inputtingRight)
			returnForce.x = acc_inAir;
		else if (inputtingLeft)
			returnForce.x = -acc_inAir;
		break;
		
	}

	return returnForce;
}

/*!
@brief Action状態から、その時の速度の限界値を得る。方向も考慮しており、扱うのは速度が前提。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::getLimitVelFromAction(characterAction nowAction, bool isDireRight, VirtualController controller)
{
	Dimention returnVelocity;

	returnVelocity.x = returnVelocity.y = 128;

	bool inputtingRight = controller.on_right;
	bool inputtingLeft = controller.on_left;

	// 歩く・走るの時は常に空中の速度の上限を代入し続ける。
	if (nowAction == characterAction::Run || nowAction == characterAction::Walk) {
		if (isDireRight) {
			limVel_inAir_jumpUp = std::abs(now_vel.x);
			if(std::abs(now_vel.x) < limVel_walk)
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

	if(preAction == characterAction::Walk || preAction == characterAction::Run)
		limVel_inAir = limVel_inAir_jumpUp;

	// 空中で方向転換したかどうか。
	if (nowAction == characterAction::Jump_Up || nowAction == characterAction::Jump_MidAir ||
		nowAction == characterAction::Jump_Fall || nowAction == characterAction::Fall) {
		preJumpingDireRight = isDireRight;

		if (preJumpingDireRight != nowJumpingDireRight) {
			if (inputtingRight) {
				limVel_inAir = limVel_inAir_afterJump;
			}
			if (inputtingLeft) {
				limVel_inAir = -limVel_inAir_afterJump;
			}
		}

		nowJumpingDireRight = preJumpingDireRight;
	}

	nowJumpingDireRight = preJumpingDireRight = isDireRight;

	switch (nowAction) {
	case characterAction::Walk:
		if(isDireRight)
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
@brief その時の加速度から、次の速度を計算する。返すのは速度。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, characterAction nowAction, bool isDireRight, VirtualController controller)
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
		returnVelocity.x = getLimitVelFromAction(nowAction, isDireRight,controller).x;

	if (returnVelocity.y > blockHeight)
		returnVelocity.y = blockHeight;
	else
		returnVelocity.y += affectAcc.y;

	return returnVelocity;
}

/*!
@brief 速度と向く方向が異なるとき（例えばBrake）に、加速度が逆方向にかかりすぎないように制御する関数。返すのは速度。
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::matchingVelAndDireHorizon(Dimention affectedVel, characterAction nowAction, bool isDireRight)
{
	Dimention returnVel = affectedVel;

	if (nowAction == characterAction::Jump_Up ||
		nowAction == characterAction::Jump_MidAir ||
		nowAction == characterAction::Jump_Fall ||
		nowAction == characterAction::Fall) {
		return returnVel;
	}

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
Dimention Pysical::update(characterAction nowAction, bool isDireRight, VirtualController controller, std::shared_ptr<CollisionDetect> _collision)
{

	// Actionが切り替わったら時間を０にする。
	if (isSwitching(nowAction))
		timeInAction = 0;

	// 初速度を有効にする。
	now_vel = affectInitVelocity(now_vel, nowAction, timeInAction, controller);

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

	timeInAction++;
	timeFromBorn++;

	//DrawFormatString(100, 70, GetColor(255, 255, 255), "now acc x:%d, y:%d", now_acc.x, now_acc.y);
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
		retVec.y = -static_cast<int>(static_cast<float>(retVec.y) * coef_block);

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