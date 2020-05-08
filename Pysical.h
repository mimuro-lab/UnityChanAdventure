
/*!
@file Pysical.h
@brief PredictPointクラスが定義されているヘッダファイル。
@date 2020/05/04/19:09
@author mimuro
*/

#pragma once
#include "Define.h"
#include "CollisionDetect.h"

/*!
@class Pysical
@brief 物理演算に置いて速度の演算を担うクラス。
@date 2020/05/04/19:12
@author mimuro
*/
using namespace Define;

class Pysical {

	//! 現在の速度を管理する変数。
	Dimention now_vel;

	//! 現在の加速度を管理する変数。
	Dimention now_acc;

	//! Action中の時間、Actionが切り替わると０にリセットされる。
	unsigned short int time = 0;

	// moveNコマに一回加速度を加える。
	unsigned char addAccN = 2;
	unsigned char addAccCounter = 0;

	//! 重力の値
	unsigned char acc_gravity = 1;

	//! 摩擦力の値
	unsigned char acc_friction = 1;

	//! ブロックとの反発係数(割る数、大きいと速度は小さくなる)
	float coef_block = 0.3;

	// Actionごとの加速度の大きさと速度の限界値
	unsigned char acc_brake = 0;

	unsigned char acc_walk = 1;
	unsigned char limVel_walk = 3;

	unsigned char acc_run = 1;
	unsigned char limVel_run = 7;

	unsigned char initVel_jumpUp = 12;
	unsigned char initVel_jumpMidAir = 3;

	//! 初速度を格納する変数。
	std::vector<Dimention> _isInitVelocity;

	//! そのアクション状態の時に重力を有効にするかどうかを管理する変数。
	std::vector<bool> _validGravityAction;

	//! そのアクション状態の時に摩擦力を有効にするかどうかを管理する変数。
	std::vector<bool> _validFrictionAction;

	//! 対象の速度に対し、初速度をさらに与える関数。
	Dimention affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned short nowTime);

	//! affectGravity（対象の加速度）に対し、重力を加える。
	Dimention affectGravity(Dimention affectedAcc, rollAction_Basic nowAction);

	//! affectGravity（対象の加速度）に対し、さらに地面との摩擦を加える。
	Dimention affectFriction(Dimention affectedAcc, rollAction_Basic nowAction, bool isDireRight);

	//! アクション状態とその方向から加速度を得る。
	Dimention getForceFromAction(rollAction_Basic nowAction, bool isDireRight);

	//! アクション状態とその方向から速度の限界値を得る。
	Dimention getLimitVelFromAction(rollAction_Basic nowAction, bool isDireRight);
	
	//! 加速度から速度を計算する。
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, rollAction_Basic nowAction, bool isDireRight);

	//! 向いている方向と速度方向が違うときは速度を0にする。（水平方向のみ）
	Dimention matchingVelAndDireHorizon(Dimention affectedVel, bool isDireRight);

	//! 速度を当たり判定によりリセットする。
	Dimention resetByCollision(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);
		
	rollAction_Basic preIsAction = rollAction_Basic::Idle;
	//! Actionが切り替わった瞬間を取得する関数
	bool isSwitching(Define::rollAction_Basic nowAction) {
		bool ret = false;
		if (nowAction != preIsAction)	ret = true;
		else							ret = false;
		preIsAction = nowAction;
		return ret;
	}

public:

	Pysical()
	{
		now_vel.x = now_vel.y = 0;
		now_acc.x = now_acc.y = 0;

		Dimention initVel;
		initVel.x = initVel.y = 0;
		_isInitVelocity = std::vector<Dimention>(static_cast<int>(Define::rollAction_Basic::_end), initVel);
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_Up)].y = - initVel_jumpUp;
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)].y = -initVel_jumpMidAir;

		_validGravityAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validGravityAction[static_cast<int>(Define::rollAction_Basic::Fall)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_Up)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Brake)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Crouch)]
			= true;

		_validFrictionAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validFrictionAction[static_cast<int>(Define::rollAction_Basic::Idle)]
			= _validFrictionAction[static_cast<int>(Define::rollAction_Basic::Brake)]
			= _validFrictionAction[static_cast<int>(Define::rollAction_Basic::Crouch)]
			= _validFrictionAction[static_cast<int>(Define::rollAction_Basic::Jump_Landing)]
			= true;
	};
	~Pysical() = default;


	//! アクション状態とその方向により速度と加速度を更新し、速度を返す。
	Dimention update(rollAction_Basic nowAction, bool isDireRight);

	//! 座標をセットした後、適切に速度をリセットする。
	Dimention resetVelocity(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);
};