
/*!
@file Player.cpp
@brief Playerクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"

/*!
@brief プレイヤーオブジェクトの座標更新、アニメーションの処理などを行う。
@date 2020/04/21/12:36
@author mimuro
*/
void Player::update(std::shared_ptr<Stage> _stage)
{
	// Collisionの更新を行う。
	collision->update(playerStatus, _stage);

	// Statusの更新処理を行う。
	playerStatus = updateStatus(playerStatus, collision, _stage);
	
	// アニメーションの下処理を行う。
	animation->update(playerStatus);

	//// 次のアクションを現在の条件によって選択していく。
	// 次のアクションを格納しておく変数。
	Define::rollAction_Basic _next;

	// 今の状態が途中切り替えＯＫまたは、途中切り替えＮＧかつアニメーションが終了したら、、、アクション切り替えする可能性。
	if (IsAction_canSwitching[static_cast<int>(IsAction)] ||
		(!IsAction_canSwitching[static_cast<int>(IsAction)] && animation->isEnd())) {

		// _nextへ次のシーンを取得する。
		_next = getNextAction(collision, animation);

		// 現在のアクションと異なるアクションが次のアクションだったら、、、
		if (IsAction != _next) {

			// アニメーションオブジェクトを更新し、終了。
			animation = switchingAnimation(_next);
			return;
		}
		
		// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
		// switchingAnimation()を実行せずに関数を終了。
		if (IsAction == Define::rollAction_Basic::Crouch)
			return;	
		
		// 同じアクションが入力され続けて、現在のアニメーションが終了したら現在のアニメーションをリフレッシュする。
		// また、次のコマでの上記の処理"_next = getNextAction();"で再度その状態が更新される。
		if (animation->isEnd()) {
			animation->refreshing();
			return;
		}
	}


}

void Player::draw()
{
	animation->draw();
	collision->draw();
}

/*!

*/

Define::Status Player::updateStatus(Define::Status _nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = _nowStatus;

	switch (IsAction) {
	case Define::rollAction_Basic::Brake:
		_nextStatus = animationMove->updateBrake(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Crouch:
		_nextStatus = animationMove->updateCrouch(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Damage:
		_nextStatus = animationMove->updateDamage(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Idle:
		_nextStatus = animationMove->updateIdle(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Jump_Fall:
		_nextStatus = animationMove->updateJump_Fall(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Jump_Landing:
		_nextStatus = animationMove->updateJump_Landing(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Jump_MidAir:
		_nextStatus = animationMove->updateJump_MidAir(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Jump_Up:
		_nextStatus = animationMove->updateJump_Up(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Fall:
		_nextStatus = animationMove->updateFall(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Run:
		_nextStatus = animationMove->updateRun(_nowStatus, _collision, _stage);
		break;
	case Define::rollAction_Basic::Walk:
		_nextStatus = animationMove->updateWalk(_nowStatus, _collision, _stage);
	}

	return _nextStatus;
}

/*!
@biref コントローラの入力状態によって次のアクション状態を取得する。playerStatusの更新はここでは行わない。状態を決定する処理だけ。
@date 2020/04/21/18:30
@author mimuro
*/
Define::rollAction_Basic Player::getNextAction(std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Animation> _animation)
{
	// Jump_MidAir
	if (IsAction == Define::rollAction_Basic::Jump_Up && animation->isEnd()) {
		return Define::rollAction_Basic::Jump_MidAir;
	}

	// Jump_Landing
	if (IsAction == Define::rollAction_Basic::Fall && _collision->getCollisionedSide().bottom) {
		return Define::rollAction_Basic::Jump_Landing;
	}

	// Fall
	if (!_collision->getCollisionedSide().bottom) {
		return Define::rollAction_Basic::Fall;
	}

	// Brake
	if (IsAction == Define::rollAction_Basic::Run) {
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
std::shared_ptr<Animation> Player::switchingAnimation(Define::rollAction_Basic next)
{

	switch (next) {
	case Define::rollAction_Basic::Brake:
		IsAction = Define::rollAction_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, playerStatus);
		break;
	case Define::rollAction_Basic::Crouch:
		IsAction = Define::rollAction_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus, 6, 99, true);
		break;
	case Define::rollAction_Basic::Damage:
		IsAction = Define::rollAction_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, playerStatus);
		break;
	case Define::rollAction_Basic::Idle:
		IsAction = Define::rollAction_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
		break;
	case Define::rollAction_Basic::Jump_Fall:
		IsAction = Define::rollAction_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, playerStatus);
		break;
	case Define::rollAction_Basic::Jump_Landing:
		IsAction = Define::rollAction_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, playerStatus);
		break;
	case Define::rollAction_Basic::Jump_MidAir:
		IsAction = Define::rollAction_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, playerStatus);
		break;
	case Define::rollAction_Basic::Jump_Up:
		IsAction = Define::rollAction_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, playerStatus);
		break;
	case Define::rollAction_Basic::Fall:
		IsAction = Define::rollAction_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, playerStatus);
		break;
	case Define::rollAction_Basic::Run:
		IsAction = Define::rollAction_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, playerStatus);
		break;
	case Define::rollAction_Basic::Walk:
		IsAction = Define::rollAction_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, playerStatus);
		break;
	}

	// エラー処理、何も選択されなかったら取り合えずアイドリング状態にする。
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
}

