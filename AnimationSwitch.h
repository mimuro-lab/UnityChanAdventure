
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
#include "ImagePath_Unitychan.h"
#include "PlayerStatus.h"
#include "VirtualController.h"
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

	//! アクション中に他のアクションに切り替え可能かどうか？（添え字がcharacterActionに対応）
	vector<bool> IsAction_canSwitching;

	//// 次のアクションを現在の条件によって選択していく。
	//! 次のアクションを格納しておく変数。
	characterAction nextAction;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Status playerStatus;

	//! 剣アクションを次のコンボにするかどうか。
	bool soardCombContinue = false;

	//! アクション状態を切り替えてもよいかを返す。
	bool acceptSwitching(shared_ptr<Animation> animation, characterAction nowAction);

	//! コントローラの入力などに応じた次のアクションを取得する。
	characterAction getNextAction(
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Animation> _animation, 
		Status playerStatus,
		characterAction nowAction
		, VirtualController controller);
	
	//! getNextActionにより得た次のアクション状態を適応されてよいかどうかを返す関数。
	bool acceptNextAction(characterAction nowAction, characterAction nextAction, Status _playerStatus);

	//! animationをリフレッシュしてもよいか判断する関数。
	bool isRefresh(characterAction nowAction, shared_ptr<Animation> __animation);
	

	//! 剣攻撃のコンボ数処理
	bool getSoardComb(characterAction nowAction, shared_ptr<Animation> __animation, bool nowCombContinue, VirtualController controller);

protected:

	//! プレイヤーオブジェクトの現在の状態を管理。
	characterAction nowAction;

	//! アニメーションを切り替える関数。
	virtual shared_ptr<Animation> switchingAnimation(characterAction next, Status _playerStatus);

public:
	AnimationSwitch(characterAction initAction = characterAction::Walk)
	{ 
		// nowActionは最初、Fallから始める。
		nowAction = initAction;
		
		// IsAction_canSwitchinの初期化。 Idle, Walk, Run, Fallの状態のときは切り替え可能の状態。
		IsAction_canSwitching = vector<bool>(static_cast<int>(characterAction::_end), false);

		IsAction_canSwitching[static_cast<int>(characterAction::Idle)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Walk)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Run)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Fall)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Jump_Up)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Jump_MidAir)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Jump_Fall)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Hundgun_init)]
			= IsAction_canSwitching[static_cast<int>(characterAction::Hundgun_horizonal)]
			= true;
	};
	~AnimationSwitch() = default;

	//! 更新を行う関数。
	shared_ptr<Animation> update(
		shared_ptr<CollisionDetect> collision,
		shared_ptr<Animation> animation,
		Status playerStatus,
		VirtualController controller);

	//! 現在どのアクション状態かを取得する関数。
	characterAction getNowAction() { return nowAction; }

};

