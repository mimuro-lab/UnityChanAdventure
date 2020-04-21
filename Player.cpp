
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
void Player::update()
{
	// Statusの更新処理を行う。
	playerStatus = updateStatus(playerStatus);
	
	// アニメーションの下処理を行う。
	animation->update(playerStatus);

	//// 次のアクションを現在の条件によって選択していく。
	// 次のアクションを格納しておく変数。
	playerAction _next;

	// 今の状態が途中切り替えＯＫまたは、途中切り替えＮＧかつアニメーションが終了したら、、、アクション切り替えする可能性。
	if (IsAction_canSwitching[IsAction] || 
		(!IsAction_canSwitching[IsAction] && animation->isEnd())) {

		// _nextへ次のシーンを取得する。
		_next = getNextAction();

		// 現在のアクションと異なるアクションが次のアクションだったら、、、
		if (IsAction != _next) {

			// アニメーションオブジェクトを更新し、終了。
			animation = switchingAnimation(_next);
			return;
		}
		
		// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
		// switchingAnimation()を実行せずに関数を終了。
		if (IsAction == Crouch)
			return;	
		
		// 同じアクションが入力され続けて、現在のアニメーションが終了したらとりあえずIdling状態にに設定
		// 次のコマでの上記の処理"_next = getNextAction();"で再度その状態が更新されるので入力され続けられるアクションで更新。
		if (animation->isEnd()) {

			animation = switchingAnimation(Idle);
			return;
		}
	}
}

void Player::draw()
{
	animation->draw();
}

/*!

*/

Define::Status Player::updateStatus(Define::Status _nowStatus)
{
	Define::Status _nextStatus = _nowStatus;

	switch (IsAction) {
	case Brake:
		break;
	case Crouch:
		break;
	case Damage:
		break;
	case Idle:
		break;
	case Jump_Fall:
		break;
	case Jump_Landing:
		break;
	case Jump_MidAir:
		break;
	case Jump_Up:
		break;
	case Run:
		if (playerStatus.directRight)
			_nextStatus._x += speed_run;
		else
			_nextStatus._x -= speed_run;
		break;
	case Walk:
		if (playerStatus.directRight)
			_nextStatus._x += speed_walk;
		else
			_nextStatus._x -= speed_walk;
		break;
	}

	return _nextStatus;
}

/*!
@biref コントローラの入力状態によって次のアクション状態を取得する。playerStatusの更新はここでは行わない。状態を決定する処理だけ。
@date 2020/04/21/18:30
@author mimuro
*/
Player::playerAction Player::getNextAction()
{
	// Brake
	if (IsAction == Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft()) 
			return Brake;
	}

	// Jump
	if (Controller::getIns()->getOn_A()) {
		return Jump_Up;
	}

	// Crouch
	if (Controller::getIns()->getOnDown()) {
		return Crouch;
	}

	// Run R
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Run;
	}
	
	// Run L
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Run;
	}

	// Walk R
	if (Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Walk;
	}

	// Walk L
	if (Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Walk;
	}

	// 何も入力されなければIdling状態にする。
	return Idle;

}

/*!
@brief IsActionを更新して、次のアクションのAnimation型のオブジェクトを返す。
@date 2020/04/21/18:33
@author mimuro
*/
std::shared_ptr<Animation> Player::switchingAnimation(playerAction next)
{
	switch (next) {
	case Brake:
		IsAction = Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, playerStatus);
		break;
	case Crouch:
		IsAction = Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus, 6, 99, true);
		break;
	case Damage:
		IsAction = Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, playerStatus);
		break;
	case Idle:
		IsAction = Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
		break;
	case Jump_Fall:
		IsAction = Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, playerStatus);
		break;
	case Jump_Landing:
		IsAction = Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, playerStatus);
		break;
	case Jump_MidAir:
		IsAction = Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, playerStatus);
		break;
	case Jump_Up:
		IsAction = Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, playerStatus);
		break;
	case Run:
		IsAction = Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, playerStatus);
		break;
	case Walk:
		IsAction = Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, playerStatus);
		break;
	}
}

