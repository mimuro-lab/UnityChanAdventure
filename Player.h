
/*!
@file Player.h
@brief Playerクラスが定義されているヘッダファイル
@date 2020/04/21/12:26
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include "Task.h"
#include "Define.h"
#include "imagePath.h"
#include "Controller.h"
#include "Animation.h"
#include <memory>

/*!
@class Player
@brief Playerキャラの処理全般を担うクラス。
@date 2020/04/21/12:28
@author mimuro
*/
class Player :
	public Task
{

	//! 歩く速度
	char speed_walk = 2;
	//! 走る速度
	char speed_run = 4;

	//! プレイヤーオブジェクトの行動の分類。
	enum playerAction {
		Brake, Crouch, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Run, Walk, _end
	};

	//! プレイヤーオブジェクトの現在の状態を管理。
	playerAction IsAction;

	//! アクション中に他のアクションに切り替え可能かどうか？（添え字がplayerActionに対応）
	std::vector<bool> IsAction_canSwitching;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Define::Status playerStatus;

	//! アニメーションの処理をまとめて行うオブジェクト。
	std::shared_ptr<Animation> animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);

	//! アニメーションを切り替える関数。
	std::shared_ptr<Animation> switchingAnimation(playerAction next);

	//! コントローラの入力などに応じた次のアクションを取得する。
	playerAction getNextAction();

	//! プレイヤーオブジェクトのStatusの更新を行う。
	Define::Status updateStatus(Define::Status _nowStatus);
public:

	Player() : 
		IsAction(Idle)
	{
		// 初期情報の設定。
		/*
		playerStatus._x = Define::WIN_W / 2;
		playerStatus._y = Define::WIN_H / 2;
		*/
		playerStatus._x = 200;
		playerStatus._y = 100;
		playerStatus.directRight = true;

		// IsAction_canSwitchinの初期化。 Idle, Walk, Runの状態のときは切り替え可能の状態。
		IsAction_canSwitching = std::vector<bool>(_end, false);
		IsAction_canSwitching[Idle] = IsAction_canSwitching[Walk] = IsAction_canSwitching[Run] = true;

	};

	~Player() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	void update() override;

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw() override;
};
