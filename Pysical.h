#pragma once
#include "Define.h"
#include "CollisionDetect.h"

using namespace Define;

class Pysical {

	Dimention now_vel;
	Dimention now_acc;

	// Action中の時間、Actionが切り替わると０にリセットされる。
	unsigned short int time = 0;

	unsigned char acc_gravity = 1;

	unsigned char acc_brake = 1;

	unsigned char acc_walk = 2;

	unsigned char acc_run = 3;

	std::vector<Dimention> _isInitVelocity;
	std::vector<bool> _validGravityAction;
	std::vector<bool> _validBrakingAction;

	// 対象の速度に対し、初速度をさらに与える。
	Dimention affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned char nowTime);

	// affectGravity（対象の加速度）に対し、重力を加える。
	Dimention affectGravity(Dimention affectedAcc, rollAction_Basic nowAction);

	// affectGravity（対象の加速度）に対し、さらに地面との摩擦を加える。
	Dimention affectBraking(Dimention affectedAcc, rollAction_Basic nowAction);

	// アクション状態とその方向から加速度を得る。
	Dimention getForceFromAction(rollAction_Basic nowAction, bool isDireRight);

	// 加速度から速度を計算する。
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc);

	// 向いている方向と速度方向が違うときは速度を0にする。（水平方向のみ）
	Dimention matchingVelAndDireHorizon(Dimention affectedVel, bool isDireRight);

	// Actionが切り替わった瞬間を取得する関数
	rollAction_Basic preIsAction = rollAction_Basic::Idle;
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
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_Up)].y = - 10;
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)].y = -5;

		_validGravityAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validGravityAction[static_cast<int>(Define::rollAction_Basic::Fall)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_Up)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)]
			= true;

		_validBrakingAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validBrakingAction[static_cast<int>(Define::rollAction_Basic::Idle)]
			= true;
	};
	~Pysical() = default;


	// アクション状態とその方向により速度と加速度を更新し、速度を返す。
	Dimention update(rollAction_Basic nowAction, bool isDireRight);

};