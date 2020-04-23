
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
	playerAction _next;

	// 今の状態が途中切り替えＯＫまたは、途中切り替えＮＧかつアニメーションが終了したら、、、アクション切り替えする可能性。
	if (IsAction_canSwitching[IsAction] || 
		(!IsAction_canSwitching[IsAction] && animation->isEnd())) {

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
		if (IsAction == playerAction::Crouch)
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
	case playerAction::Brake:
		_nextStatus = animationMove->updateBrake(_nowStatus, _collision, _stage);
		break;
	case playerAction::Crouch:
		_nextStatus = animationMove->updateCrouch(_nowStatus, _collision, _stage);
		break;
	case playerAction::Damage:
		_nextStatus = animationMove->updateDamage(_nowStatus, _collision, _stage);
		break;
	case playerAction::Idle:
		_nextStatus = animationMove->updateIdle(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_Fall:
		_nextStatus = animationMove->updateJump_Fall(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_Landing:
		_nextStatus = animationMove->updateJump_Landing(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_MidAir:
		_nextStatus = animationMove->updateJump_MidAir(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_Up:
		_nextStatus = animationMove->updateJump_Up(_nowStatus, _collision, _stage);
		break;
	case playerAction::Fall:
		_nextStatus = animationMove->updateFall(_nowStatus, _collision, _stage);
		break;
	case playerAction::Run:
		_nextStatus = animationMove->updateRun(_nowStatus, _collision, _stage);
		break;
	case playerAction::Walk:
		_nextStatus = animationMove->updateWalk(_nowStatus, _collision, _stage);
	}

	return _nextStatus;
}

/*!
@biref コントローラの入力状態によって次のアクション状態を取得する。playerStatusの更新はここでは行わない。状態を決定する処理だけ。
@date 2020/04/21/18:30
@author mimuro
*/
Player::playerAction Player::getNextAction(std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Animation> _animation)
{
	// Jump_MidAir
	if (IsAction == playerAction::Jump_Up && animation->isEnd()) {
		return playerAction::Jump_MidAir;
	}

	// Jump_Landing
	if (IsAction == playerAction::Fall && _collision->getCollisionedSide().bottom) {
		return playerAction::Jump_Landing;
	}

	// Fall
	if (!_collision->getCollisionedSide().bottom) {
		return playerAction::Fall;
	}

	// Brake
	if (IsAction == playerAction::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return playerAction::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft()) 
			return playerAction::Brake;
	}

	// Jump
	if (Controller::getIns()->getPush_A()) {
		return playerAction::Jump_Up;
	}


	// Crouch
	if (Controller::getIns()->getOnDown()) {
		return playerAction::Crouch;
	}

	// Run R
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return playerAction::Run;
	}
	
	// Run L
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return playerAction::Run;
	}

	// Walk R
	if (Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return playerAction::Walk;
	}

	// Walk L
	if (Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return playerAction::Walk;
	}

	// 何も入力されなければIdling状態にする。
	return playerAction::Idle;

}

/*!
@brief IsActionを更新して、次のアクションのAnimation型のオブジェクトを返す。
@date 2020/04/21/18:33
@author mimuro
*/
std::shared_ptr<Animation> Player::switchingAnimation(playerAction next)
{

	switch (next) {
	case playerAction::Brake:
		IsAction = playerAction::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, playerStatus);
		break;
	case playerAction::Crouch:
		IsAction = playerAction::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus, 6, 99, true);
		break;
	case playerAction::Damage:
		IsAction = playerAction::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, playerStatus);
		break;
	case playerAction::Idle:
		IsAction = playerAction::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
		break;
	case playerAction::Jump_Fall:
		IsAction = playerAction::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, playerStatus);
		break;
	case playerAction::Jump_Landing:
		IsAction = playerAction::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, playerStatus);
		break;
	case playerAction::Jump_MidAir:
		IsAction = playerAction::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, playerStatus);
		break;
	case playerAction::Jump_Up:
		IsAction = playerAction::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, playerStatus);
		break;
	case playerAction::Fall:
		IsAction = playerAction::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, playerStatus);
		break;
	case playerAction::Run:
		IsAction = playerAction::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, playerStatus);
		break;
	case playerAction::Walk:
		IsAction = playerAction::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, playerStatus);
		break;
	}

	// エラー処理、何も選択されなかったら取り合えずアイドリング状態にする。
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
}

