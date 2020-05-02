#include "AnimationSwitch.h"

std::shared_ptr<Animation> AnimationSwitch::update(
	std::shared_ptr<CollisionDetect> collision, 
	std::shared_ptr<Animation> animation, 
	Define::Status playerStatus)
{

	// アニメーションを切り替えてもよいなら、
	if (acceptSwitching(animation, nowAction)) {
		// _nextへ次のシーンを取得する。
		nextAction = getNextAction(collision, animation, playerStatus, nowAction);
		if(acceptNextAction(nowAction, nextAction, playerStatus)) {
			// アニメーションオブジェクトを更新し、終了。
			nowAction = nextAction;
			return switchingAnimation(nextAction, playerStatus);
		}

		// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
		// switchingAnimation()を実行せずに関数を終了。(refreshせずに終了)
		if (isRefresh(nextAction, animation)) {
			std::shared_ptr<Animation> returnAnimation = animation;
			returnAnimation->refreshing();
			return returnAnimation;
		}
	}

	return animation;

}

bool AnimationSwitch::acceptSwitching(std::shared_ptr<Animation> animation, Define::rollAction_Basic nowAction)
{
	// 今の状態が途中切り替えＯＫだったら切り替えＯＫ
	if (IsAction_canSwitching[static_cast<int>(nowAction)])
		return true;

	// 途中切り替えＮＧかつアニメーションが終了したら切り替えＯＫ
	if(!IsAction_canSwitching[static_cast<int>(nowAction)] && animation->isEnd())
		return true;

	return false;
}

bool AnimationSwitch::acceptNextAction(Define::rollAction_Basic nowAction, Define::rollAction_Basic nextAction, Define::Status _playerStatus)
{

	// 現在のアクションと同じアクションが次のアクションだったら切り替えない。
	if (nowAction == nextAction)
		return false;

	//Jump_MidAirの時は、速度上向きの間はアニメーションを切り替えない。
	if (nowAction == Define::rollAction_Basic::Jump_MidAir && playerStatus._y_speed < 0)
		return false;

	// 上記の条件に当てはまらないのなら切り替える。
	return true;
}

bool AnimationSwitch::isRefresh(Define::rollAction_Basic nowAction, std::shared_ptr<Animation> animation)
{
	// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
	// switchingAnimation()を実行せずに関数を終了。(refreshせずに終了)
	if (nowAction == Define::rollAction_Basic::Crouch )
		return false;
	
	if (nowAction == Define::rollAction_Basic::Jump_MidAir)
		return false;

	// 同じアクションが入力され続けて、現在のアニメーションが終了したら現在のアニメーションをリフレッシュする。
	// また、次のコマでの上記の処理"_next = getNextAction();"で再度その状態が更新される。
	if (!animation->isEnd())
		return false;

	// 上記の条件に当てはまらないのならリフレッシュする。
	return true;
}

/*!
@biref コントローラの入力状態によって次のアクション状態を取得する。playerStatusの更新はここでは行わない。状態を決定する処理だけ。
@date 2020/04/21/18:30
@author mimuro
*/
Define::rollAction_Basic AnimationSwitch::getNextAction(
	std::shared_ptr<CollisionDetect> collision, 
	std::shared_ptr<Animation> animation, 
	Define::Status playerStatus,
	Define::rollAction_Basic nowAction)
{

	// Jump_Up to Jump_MidAir
	if (nowAction == Define::rollAction_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return Define::rollAction_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (nowAction == Define::rollAction_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return Define::rollAction_Basic::Fall;
	}

	// Jump_Landing
	if (nowAction == Define::rollAction_Basic::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return Define::rollAction_Basic::Jump_Landing;
	}

	// Fall
	if (!collision->getCollisionedSide().bottom) {
		return Define::rollAction_Basic::Fall;
	}

	// Brake
	if (nowAction == Define::rollAction_Basic::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return Define::rollAction_Basic::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft())
			return Define::rollAction_Basic::Brake;
	}

	// Jump
	if (Controller::getIns()->getPush_A()) {
		return Define::rollAction_Basic::Jump_Up;
	}


	// Crouch
	if (Controller::getIns()->getOnDown()) {
		return Define::rollAction_Basic::Crouch;
	}

	// Run R
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Define::rollAction_Basic::Run;
	}

	// Run L
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Define::rollAction_Basic::Run;
	}

	// Walk R
	if (Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Define::rollAction_Basic::Walk;
	}

	// Walk L
	if (Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Define::rollAction_Basic::Walk;
	}

	// 何も入力されなければIdling状態にする。
	return Define::rollAction_Basic::Idle;

}

/*!
@brief IsActionを更新して、次のアクションのAnimation型のオブジェクトを返す。
@date 2020/04/21/18:33
@author mimuro
*/
std::shared_ptr<Animation> AnimationSwitch::switchingAnimation(Define::rollAction_Basic next, Define::Status nowStatus)
{
	using namespace std;
	switch (next) {
	case Define::rollAction_Basic::Brake:
		nowAction = Define::rollAction_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, nowStatus);
		break;
	case Define::rollAction_Basic::Crouch:
		nowAction = Define::rollAction_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, nowStatus);
		break;
	case Define::rollAction_Basic::Damage:
		nowAction = Define::rollAction_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, nowStatus);
		break;
	case Define::rollAction_Basic::Idle:
		nowAction = Define::rollAction_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
		break;
	case Define::rollAction_Basic::Jump_Fall:
		nowAction = Define::rollAction_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case Define::rollAction_Basic::Jump_Landing:
		nowAction = Define::rollAction_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case Define::rollAction_Basic::Jump_MidAir:
		nowAction = Define::rollAction_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, nowStatus, 3, 99, true);
		break;
	case Define::rollAction_Basic::Jump_Up:
		nowAction = Define::rollAction_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case Define::rollAction_Basic::Fall:
		nowAction = Define::rollAction_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, nowStatus);
		break;
	case Define::rollAction_Basic::Run:
		nowAction = Define::rollAction_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, nowStatus);
		break;
	case Define::rollAction_Basic::Walk:
		nowAction = Define::rollAction_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, nowStatus);
		break;
	}

	// エラー処理、何も選択されなかったら取り合えずアイドリング状態にする。
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
}
