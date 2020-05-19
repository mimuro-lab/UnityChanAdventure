
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
#include "AnimationSwitch.h"
#include "CollisionDetect.h"
#include "PlayerDirect.h"
#include "Stage.h"
#include "DamageObj.h"
#include <memory>
#include <vector>

/*!
@class Player
@brief Playerキャラの処理全般を担うクラス。
@date 2020/04/21/12:28
@author mimuro
*/
class Player
{

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Define::Status playerStatus;

	//! ステージを移動させる速度
	Dimention shiftingStage;

	//! アニメーションの処理をまとめて行うオブジェクト。
	std::shared_ptr<Animation> animation;

	//! アニメーション時のStatusの座標の更新をするオブジェクト。
	std::shared_ptr<AnimationMove> animationMove;

	//! プレイヤーオブジェクトの当たり判定処理をまとめて行うオブジェクト。
	std::shared_ptr<CollisionDetect> collision;

	//! アクション状態を切り替える処理をまとめて行うオブジェクト。
	std::shared_ptr<AnimationSwitch> animationSwitch;

	//! プレイヤーオブジェクトがどっちの方向に向くか決定するオブジェクト。
	std::shared_ptr<PlayerDirect> playerDirect;

public:

	Player(std::shared_ptr<Stage> _stage)
	{
		// 初期情報の設定。
		playerStatus._x = Define::WIN_W / 2;
		playerStatus._y = Define::WIN_H / 2;

		playerStatus._x_speed = playerStatus._y_speed = 0;

		playerStatus.directRight = true;

		shiftingStage.x = shiftingStage.y = 0;

		animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Fall, playerStatus);

		animationMove = std::make_shared<AnimationMove>();

		collision = std::make_shared<CollisionDetect>(_stage, playerStatus);

		animationSwitch = std::make_shared<AnimationSwitch>();

		playerDirect = std::make_shared<PlayerDirect>();

	};

	~Player() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	void update(std::shared_ptr<Stage> _stage);

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw();

	const Define::Status getStatus() { return playerStatus; }

	const Dimention getShiftingState() { return shiftingStage; }

	vector<shared_ptr<DamageObj>> generateDamageObj(vector<shared_ptr<DamageObj>> _nowDmg);

};
