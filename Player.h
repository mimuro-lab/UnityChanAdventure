
/*!
@file Player.h
@brief Playerクラスが定義されているヘッダファイル
@date 2020/04/21/12:26
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include "Define.h"
#include "imagePath.h"
#include "Controller.h"
#include "Animation.h"
#include "AnimationMove.h"
#include "CollisionDetect.h"
#include "Stage.h"
#include <memory>

/*!
@class Player
@brief Playerキャラの処理全般を担うクラス。
@date 2020/04/21/12:28
@author mimuro
*/
class Player
{

	//! 歩く速度
	char maxSpeed_walk = 5;
	//! 走る速度
	char maxSpeed_run = 10;
	//! Jump_Upの初速度
	char jumpUp_initSpeed = 20;
	//! Jump_MidAirの初速度
	char jumpMid_initSpeed = 15;

	//! プレイヤーオブジェクトの現在の状態を管理。
	Define::rollAction_Basic IsAction;

	//! アクション中に他のアクションに切り替え可能かどうか？（添え字がDefine::rollAction_Basicに対応）
	std::vector<bool> IsAction_canSwitching;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Define::Status playerStatus;

	//! アニメーションの処理をまとめて行うオブジェクト。
	std::shared_ptr<Animation> animation;

	//! アニメーション時のStatusの座標の更新をするオブジェクト。
	std::shared_ptr<AnimationMove> animationMove;

	//! プレイヤーオブジェクトの当たり判定処理をまとめて行うオブジェクト。
	std::shared_ptr<CollisionDetect> collision;

	//! アニメーションを切り替える関数。
	std::shared_ptr<Animation> switchingAnimation(Define::rollAction_Basic next);

	//! コントローラの入力などに応じた次のアクションを取得する。
	Define::rollAction_Basic getNextAction(std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Animation> _animation);

public:

	Player(std::shared_ptr<Stage> _stage) : 
		IsAction(Define::rollAction_Basic::Idle)
	{
		// 初期情報の設定。
		playerStatus._x = Define::WIN_W / 2;
		playerStatus._y = Define::WIN_H / 2;

		playerStatus.directRight = true;

		// IsAction_canSwitchinの初期化。 Idle, Walk, Run, Fallの状態のときは切り替え可能の状態。
		IsAction_canSwitching = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);

		IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Idle)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Walk)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Run)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Fall)]
			= true;

		animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);

		animationMove = std::make_shared<AnimationMove>(maxSpeed_walk, maxSpeed_run, jumpUp_initSpeed, jumpMid_initSpeed);

		collision = std::make_shared<CollisionDetect>(_stage, playerStatus);

	};

	~Player() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	void update(std::shared_ptr<Stage> _stage);

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw();
};
