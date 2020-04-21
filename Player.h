
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
	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Define::Status playerStatus;

	//! アニメーションの処理をまとめて行うオブジェクト。
	std::shared_ptr<Animation> animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, 100,100);
public:
	Player();
	~Player() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	void update() override;

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw() override;
};
