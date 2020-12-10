#pragma once

#include <DxLib.h>
#include "Define.h"
#include "ImagePath_Unitychan.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMove.h"
#include "AnimationSwitch.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "AbsDamageObj.h"
#include "CalcDamagesOverlap.h"
#include "Stage.h"
#include "EnemyStatus.h"
#include <memory>
#include <vector>

#include "Bullet.h"

using namespace Define;
using namespace std;

class Enemy
{

	char deActiveLeft = -50;
	char deActiveRight = 50;
	char deActiveHead = -50;
	char deActiveBottom = 50;

	//! コントローラ
	VirtualController controller;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Define::Status statusAsChara;

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

	std::shared_ptr<EnemyStatus> statusAsPara;

	//! Playerからのダメージオブジェクトが当たっているかを判定するオブジェクト。
	std::shared_ptr<CalcDamagesOverlap> damagesOverlap;

	vector<vector<Define::Dimention>> collisionPoints;

	vector<int> detectDmsInd;

	bool isDead = false;
	bool isEnd = false;

public:
	Enemy(std::shared_ptr<Stage> _stage, int init_x, int init_y, int init_hitpoint)
	{

		// 初期情報の設定。
		statusAsChara._x = init_x;
		statusAsChara._y = init_y;

		statusAsChara._x_speed = statusAsChara._y_speed = 0;

		statusAsChara.directRight = true;

		
		statusAsPara = std::make_shared<EnemyStatus>();

		statusAsPara->isActive = true;
		statusAsPara->isAlive = true;

		statusAsPara->HitPoint = init_hitpoint;
		statusAsPara->AllHitPoint = init_hitpoint;
		statusAsPara->lessHitPoint = init_hitpoint / 4;

		animation = std::make_shared<Animation>(ImagePath_Unitychan::getIns()->unityChan_Fall, statusAsChara);

		animationMove = std::make_shared<AnimationMove>();

		collision = std::make_shared<CollisionDetect>(_stage, statusAsChara, 10, 10, 10, 10, 15, 30, 10, 10);

		animationSwitch = std::make_shared<AnimationSwitch>();

		enemyDirect = std::make_shared<CharacterDirect>();

		damagesOverlap = std::make_shared<CalcDamagesOverlap>();

		controller.on_Y = true;

	};

	//! Playerオブジェクトの前処理全般を行う関数。
	void update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, std::vector<std::shared_ptr<AbsDamageObj>> _damages);

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw();

	const std::shared_ptr<EnemyStatus> getStatusAsParameter() { return statusAsPara; }

	void adjustBottom(int AdjustRange);

	vector<vector<Dimention>> getCollisionPoints() {
		return collisionPoints;
	}

	vector<shared_ptr<AbsDamageObj>> generateDamageObj(vector<shared_ptr<AbsDamageObj>> _nowDmg, shared_ptr<Stage> stage);

	vector<int> getDetectedDamagesIndex() {
		return detectDmsInd;
	}

};

