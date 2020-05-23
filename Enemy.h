#pragma once

#include <DxLib.h>
#include "Define.h"
#include "imagePath.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMove.h"
#include "AnimationSwitch.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "Stage.h"
#include "DamageObj.h"
#include <memory>
#include <vector>

using namespace Define;

class Enemy
{

	//! コントローラ
	VirtualController controller;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Define::Status enemyStatus;

	//! アニメーションの処理をまとめて行うオブジェクト。
	std::shared_ptr<Animation> animation;

	//! アニメーション時のStatusの座標の更新をするオブジェクト。
	std::shared_ptr<AnimationMove> animationMove;

	//! プレイヤーオブジェクトの当たり判定処理をまとめて行うオブジェクト。
	std::shared_ptr<CollisionDetect> collision;

	//! アクション状態を切り替える処理をまとめて行うオブジェクト。
	std::shared_ptr<AnimationSwitch> animationSwitch;

	//! プレイヤーオブジェクトがどっちの方向に向くか決定するオブジェクト。
	std::shared_ptr<CharacterDirect> enemyDirect;

public:
	Enemy(std::shared_ptr<Stage> _stage, int init_x, int init_y)
	{
		// 初期情報の設定。
		enemyStatus._x = init_x;
		enemyStatus._y = init_y;

		enemyStatus._x_speed = enemyStatus._y_speed = 0;

		enemyStatus.directRight = true;


		animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Fall, enemyStatus);

		animationMove = std::make_shared<AnimationMove>();

		collision = std::make_shared<CollisionDetect>(_stage, enemyStatus);

		animationSwitch = std::make_shared<AnimationSwitch>();

		enemyDirect = std::make_shared<CharacterDirect>();

	};

	//! Playerオブジェクトの前処理全般を行う関数。
	void update(std::shared_ptr<Stage> _stage, Dimention shiftingStage);

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw();

};

