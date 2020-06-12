#pragma once
#include <DxLib.h>
#include "Define.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMoveSword.h"
#include "AnimationSwitchSword.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "Stage.h"
#include "AbsDamageObj.h"
#include <memory>
#include <vector>

using namespace std;
using namespace Define;

class Sword : public AbsDamageObj
{
	int damagePointLeftUp_x = 0;
	int damagePointLeftUp_y = 0;

	int damage = 0;

	int livingTime = 10;
	int livingCounter = 0;

	//! 仮想コントローラ
	VirtualController controller;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Status damageStatus;

	//! アニメーションの処理をまとめて行うオブジェクト。
	shared_ptr<Animation> animation;

	//! アニメーション時のStatusの座標の更新をするオブジェクト。
	shared_ptr<AnimationMoveSword> animationMove;

	//! プレイヤーオブジェクトの当たり判定処理をまとめて行うオブジェクト。
	shared_ptr<CollisionDetect> collision;

	//! アクション状態を切り替える処理をまとめて行うオブジェクト。
	shared_ptr<AnimationSwitchSword> animationSwitch;

	//! プレイヤーオブジェクトがどっちの方向に向くか決定するオブジェクト。
	shared_ptr<CharacterDirect> damageDirect;

public:
	Sword(shared_ptr<Stage> _stage, int init_x, int init_y, bool isDireRight) {
		// 初期情報の設定。
		damageStatus._x = init_x;
		damageStatus._y = init_y;

		damageStatus.directRight = true;


		animation = make_shared<Animation>(ImagePath_Object::getIns()->bulletNormal, damageStatus, 0, 0, 6, 99, isDireRight, 0.2);

		animationMove = make_shared<AnimationMoveSword>(0, 0, isDireRight);

		collision = make_shared<CollisionDetect>(_stage, damageStatus, 3, 3, 3, 3, 5, 2, 5, 5);

		animationSwitch = make_shared<AnimationSwitchSword>();

		damageDirect = make_shared<CharacterDirect>();
	}

	~Sword() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	void update(std::shared_ptr<Stage> _stage, Dimention shiftingStageVel, Status playerStatus) override;

	//! Playerオブジェクトの描画処理全般を行う関数。
	void draw() override;

	void adjustBottom(int AdjustRange) override;
};

