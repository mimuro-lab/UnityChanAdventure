#pragma once
#include <DxLib.h>
#include "Define.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMoveBullet.h"
#include "AnimationSwitchBullet.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "Stage.h"
#include "AbsDamageObj.h"
#include <memory>
#include <vector>

using namespace std;
using namespace Define;

// 敵・プレイヤー・味方かかわらず、画面上のダメージ要素。
// これを生成するオブジェクトは、DamageObjないで定義された動きのみを指定。
class Bullet : public AbsDamageObj
{

	int damagePointLeftUp_x = 0;
	int damagePointLeftUp_y = 0;

	int damage = 5;

	int livingTime = 100;
	int livingCounter = 0;
	
	//! 仮想コントローラ
	VirtualController controller;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Status damageStatus;

	//! アニメーションの処理をまとめて行うオブジェクト。
	shared_ptr<Animation> animation;

	//! アニメーション時のStatusの座標の更新をするオブジェクト。
	shared_ptr<AnimationMoveBullet> animationMove;

	//! プレイヤーオブジェクトの当たり判定処理をまとめて行うオブジェクト。
	shared_ptr<CollisionDetect> collision;

	//! アクション状態を切り替える処理をまとめて行うオブジェクト。
	shared_ptr<AnimationSwitchBullet> animationSwitch;

	//! プレイヤーオブジェクトがどっちの方向に向くか決定するオブジェクト。
	shared_ptr<CharacterDirect> damageDirect;

	int toHead, toBottom, toRight, toLeft;

public:
	Bullet(shared_ptr<Stage> _stage, int init_x, int init_y, int initVel, bool isDireRight) {
		// 初期情報の設定。
		damageStatus._x = init_x;
		damageStatus._y = init_y;

		damageStatus.directRight = isDireRight;


		animation = make_shared<Animation>(ImagePath_Object::getIns()->bulletNormal, damageStatus, 0, 0, 6, 99, true, 0.2);

		animationMove = make_shared<AnimationMoveBullet>(initVel, 0, isDireRight);


		int heads, bottoms, rights, lefts;

		heads = bottoms = 1;
		rights = 3;
		lefts = 3;

		toRight = toLeft = 5;
		toHead = 5;
		toBottom = 2;

		collision = make_shared<CollisionDetect>(_stage, damageStatus, heads, bottoms, rights, lefts, toHead, toBottom, toRight, toLeft);

		animationSwitch = make_shared<AnimationSwitchBullet>();

		damageDirect = make_shared<CharacterDirect>();
	}
	~Bullet() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	void update(std::shared_ptr<Stage> _stage, Dimention shiftingStageVel, Status playerStatus) override;

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw() override;

	void adjustBottom(int AdjustRange) override;

	vector<vector<Dimention>> getCollisionPoints() override {
		return collisionPoints;
	}

	vector<int> getRange() override {
		vector<int> retRange;
		retRange.push_back(toHead);
		retRange.push_back(toBottom);
		retRange.push_back(toRight);
		retRange.push_back(toLeft);
		return retRange;
	}

	void detectEnemy() override;

	void detectPlayer() override;

	int getDamage() override {
		return damage;
	}
};

