
/*!
@file AnimationSwitch.h
@brief AnimationSwitchクラスが定義されているヘッダファイル
@date 2020/05/04/15:03
@author mimuro
*/

#pragma once
#include "CollisionDetect.h"
#include "Controller.h"
#include "Animation.h"
#include "Define.h"
#include "imagePath.h"
#include <memory>

/*!
@class AnimationSwitch
@brief アニメーションの状態を切り替える為のクラス
@date 2020/05/04/15:03
@author mimuro
*/

using namespace Define;
using namespace std;

class AnimationSwitch
{

	//! アニメーションの切り替えには、アニメーションの状態を受け取る必要がある。
	shared_ptr<Animation> _animation;

	//! アクション中に他のアクションに切り替え可能かどうか？（添え字がrollAction_Basicに対応）
	vector<bool> IsAction_canSwitching;

	//! プレイヤーオブジェクトの現在の状態を管理。
	rollAction_Basic nowAction;

	//// 次のアクションを現在の条件によって選択していく。
	//! 次のアクションを格納しておく変数。
	rollAction_Basic nextAction;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Status playerStatus;

	//! アクション状態を切り替えてもよいかを返す。
	bool acceptSwitching(shared_ptr<Animation> animation, rollAction_Basic nowAction);

	//! コントローラの入力などに応じた次のアクションを取得する。
	rollAction_Basic getNextAction(
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Animation> _animation, 
		Status playerStatus,
		rollAction_Basic nowAction);
	
	//! getNextActionにより得た次のアクション状態を適応されてよいかどうかを返す関数。
	bool acceptNextAction(rollAction_Basic nowAction, rollAction_Basic nextAction, Status _playerStatus);

	//! animationをリフレッシュしてもよいか判断する関数。
	bool isRefresh(rollAction_Basic nowAction, shared_ptr<Animation> __animation);
	
	//! アニメーションを切り替える関数。
	shared_ptr<Animation> switchingAnimation(rollAction_Basic next, Status _playerStatus);

public:
	AnimationSwitch()
	{ 
		// nowActionは最初、Fallから始める。
		nowAction = rollAction_Basic::Fall;
		
		// IsAction_canSwitchinの初期化。 Idle, Walk, Run, Fallの状態のときは切り替え可能の状態。
		IsAction_canSwitching = vector<bool>(static_cast<int>(rollAction_Basic::_end), false);

		IsAction_canSwitching[static_cast<int>(rollAction_Basic::Idle)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Walk)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Run)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Fall)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Jump_Up)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Jump_MidAir)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Jump_Fall)]
			= true;
	};
	~AnimationSwitch() = default;

	//! 更新を行う関数。
	shared_ptr<Animation> update(
		shared_ptr<CollisionDetect> collision,
		shared_ptr<Animation> animation,
		Status playerStatus);

	//! 現在どのアクション状態かを取得する関数。
	rollAction_Basic getNowAction() { return nowAction; }

};

