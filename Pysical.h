
/*!
@file Pysical.h
@brief PredictPointクラスが定義されているヘッダファイル。
@date 2020/05/04/19:09
@author mimuro
*/

#pragma once
#include "Define.h"
#include "CollisionDetect.h"
#include "VirtualController.h"

/*!
@class Pysical
@brief 物理演算に置いて速度の演算を担うクラス。
@date 2020/05/04/19:12
@author mimuro
*/
using namespace Define;

class Pysical {

protected:
	//! 現在の速度を管理する変数。
	Dimention now_vel;

	//! 現在の加速度を管理する変数。
	Dimention now_acc;

	//! Action中の時間、Actionが切り替わると０にリセットされる。
	unsigned short int timeInAction = 0;

	//! オブジェクトが生成されてからの絶対時間
	unsigned short int timeFromBorn = 0;

	// moveNコマに一回加速度を加える。
	unsigned char addAccN = 2;
	unsigned char addAccCounter = 0;

	//! 重力の値
	unsigned char acc_gravity = Accel_gravity;

	//! 摩擦力の値
	unsigned char acc_friction = 1;

	//! ブロックとの反発係数(割る数、大きいと速度は小さくなる)
	double coef_block = 0.3;

	// Actionごとの加速度の大きさと速度の限界値
	unsigned char acc_brake = 1;

	unsigned char acc_walk = 1;
	unsigned char limVel_walk = 3;

	unsigned char acc_run = 1;
	unsigned char limVel_run = 7;

	unsigned char initVel_jumpUp = 10;
	unsigned char initVel_jumpMidAir = 0;

	unsigned char acc_inAir = 2;
	char limVel_inAir_jumpUp = 0;
	unsigned char limVel_inAir_afterJump = limVel_walk;
	char limVel_inAir = 0;

	bool preJumpingDireRight = false;
	bool nowJumpingDireRight = false;

	characterAction preAction;

	//! 初速度を格納する変数。
	std::vector<Dimention> _isInitVelocity;

	//! そのアクション状態の時に重力を有効にするかどうかを管理する変数。
	std::vector<bool> _validGravityAction;

	//! そのアクション状態の時に摩擦力を有効にするかどうかを管理する変数。
	std::vector<bool> _validFrictionAction;

	//! 対象の速度に対し、初速度をさらに与える関数。
	virtual Dimention affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, VirtualController controller);

	//! affectGravity（対象の加速度）に対し、重力を加える。
	virtual Dimention affectGravity(Dimention affectedAcc, characterAction nowAction);

	//! affectGravity（対象の加速度）に対し、さらに地面との摩擦を加える。
	virtual Dimention affectFriction(Dimention affectedAcc, characterAction nowAction, bool isDireRight);

	//! アクション状態とその方向から加速度を得る。
	Dimention getForceFromAction(characterAction nowAction, bool isDireRight, VirtualController controller);

	//! アクション状態とその方向から速度の限界値を得る。
	virtual Dimention getLimitVelFromAction(characterAction nowAction, bool isDireRight, VirtualController controller);
	
	//! 加速度から速度を計算する。
	virtual Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, characterAction nowAction, bool isDireRight, VirtualController controller);

	//! 向いている方向と速度方向が違うときは速度を0にする。（水平方向のみ）
	Dimention matchingVelAndDireHorizon(Dimention affectedVel, characterAction nowAction, bool isDireRight);

	//! 速度を当たり判定によりリセットする。
	Dimention resetByCollision(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);
		
	characterAction preIsAction = characterAction::Idle;

	//! Actionが切り替わった瞬間を取得する関数
	bool isSwitching(Define::characterAction nowAction) {
		bool ret = false;
		if (nowAction != preIsAction)	ret = true;
		else							ret = false;
		preIsAction = nowAction;
		return ret;
	}

public:

	Pysical()
	{
		now_vel.x = 0;
		now_vel.y = 0;
		now_acc.x = now_acc.y = 0;

		Dimention initVel;
		initVel.x = initVel.y = 0;
		_isInitVelocity = std::vector<Dimention>(static_cast<int>(Define::characterAction::_end), initVel);
		_isInitVelocity[static_cast<int>(Define::characterAction::Jump_Up)].y = - initVel_jumpUp;
		_isInitVelocity[static_cast<int>(Define::characterAction::Jump_MidAir)].y = -initVel_jumpMidAir;

		_validGravityAction = std::vector<bool>(static_cast<int>(Define::characterAction::_end), false);
		_validGravityAction[static_cast<int>(Define::characterAction::Fall)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Jump_Up)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Jump_MidAir)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Brake)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Crouch)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Damage)]

			= _validGravityAction[static_cast<int>(Define::characterAction::Hundgun_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Hundgun_horizonal)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Hundgun_end)]

			= _validGravityAction[static_cast<int>(Define::characterAction::Soard1_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Soard2_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Soard3_init)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Soard1_end)]
			= _validGravityAction[static_cast<int>(Define::characterAction::Death)]
			= true;

		_validFrictionAction = std::vector<bool>(static_cast<int>(Define::characterAction::_end), false);
		_validFrictionAction[static_cast<int>(Define::characterAction::Idle)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Brake)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Crouch)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_Landing)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Damage)]
			
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_Up)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_MidAir)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Jump_Fall)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Fall)]

			= _validFrictionAction[static_cast<int>(Define::characterAction::Hundgun_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Hundgun_horizonal)]
		
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard1_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard2_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard3_init)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Soard1_end)]
			= _validFrictionAction[static_cast<int>(Define::characterAction::Death)]
			
			= true;
	};
	~Pysical() = default;

	//! アクション状態とその方向により速度と加速度を更新し、速度を返す。
	Dimention update(characterAction nowAction, bool isDireRight, VirtualController controller, std::shared_ptr<CollisionDetect> _collision);

	//! 座標をセットした後、適切に速度をリセットする。
	Dimention resetVelocity(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);

	const Dimention getAcc() { return now_acc; }
};