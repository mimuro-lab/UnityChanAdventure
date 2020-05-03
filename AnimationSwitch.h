#pragma once

#include "CollisionDetect.h"
#include "Controller.h"
#include "Animation.h"
#include "Define.h"
#include "imagePath.h"
#include <memory>

class AnimationSwitch
{

	std::shared_ptr<Animation> _animation;

	//! アクション中に他のアクションに切り替え可能かどうか？（添え字がDefine::rollAction_Basicに対応）
	std::vector<bool> IsAction_canSwitching;

	//! プレイヤーオブジェクトの現在の状態を管理。
	Define::rollAction_Basic nowAction;

	//// 次のアクションを現在の条件によって選択していく。
	// 次のアクションを格納しておく変数。
	Define::rollAction_Basic nextAction;

	//! プレイヤーオブジェクトの座標などの情報をまとめるオブジェクト。
	Define::Status playerStatus;


	bool acceptSwitching(std::shared_ptr<Animation> animation, Define::rollAction_Basic nowAction);

	bool acceptNextAction(Define::rollAction_Basic nowAction, Define::rollAction_Basic nextAction, Define::Status _playerStatus);

	bool isRefresh(Define::rollAction_Basic nowAction, std::shared_ptr<Animation> __animation);

	//! コントローラの入力などに応じた次のアクションを取得する。
	Define::rollAction_Basic getNextAction(
		std::shared_ptr<CollisionDetect> _collision, 
		std::shared_ptr<Animation> _animation, 
		Define::Status playerStatus,
		Define::rollAction_Basic nowAction);
	
	//! アニメーションを切り替える関数。
	std::shared_ptr<Animation> switchingAnimation(Define::rollAction_Basic next, Define::Status _playerStatus);

public:
	AnimationSwitch()
	{ 
		nowAction = Define::rollAction_Basic::Fall;
		
		// IsAction_canSwitchinの初期化。 Idle, Walk, Run, Fallの状態のときは切り替え可能の状態。
		IsAction_canSwitching = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);

		IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Idle)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Walk)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Run)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Fall)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Jump_Up)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)]
			= true;
	};
	~AnimationSwitch() = default;

	std::shared_ptr<Animation> update(
		std::shared_ptr<CollisionDetect> collision,
		std::shared_ptr<Animation> animation,
		Define::Status playerStatus);

	Define::rollAction_Basic getNowAction() { return nowAction; }

};

