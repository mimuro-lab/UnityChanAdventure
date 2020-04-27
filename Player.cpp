
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

	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。

	// Statusの更新処理を行う。
	playerStatus = animationMove->update(playerStatus, IsAction, collision, _stage, animation);

	// Collisionの更新を行う。
	collision->update(playerStatus, _stage);

	//// 次のアクションを現在の条件によって選択していく。
	// 次のアクションを格納しておく変数。
	Define::rollAction_Basic _next;

	// アニメーションの下処理を行う。
	animation->update(playerStatus);
	
	// 今の状態が途中切り替えＯＫまたは、途中切り替えＮＧかつアニメーションが終了したら、、、アクション切り替えする可能性。
	if (IsAction_canSwitching[static_cast<int>(IsAction)] ||
		(!IsAction_canSwitching[static_cast<int>(IsAction)] && animation->isEnd())) {

		// _nextへ次のシーンを取得する。
		_next = getNextAction(collision, animation);
		
		// 現在のアクションと異なるアクションが次のアクションだったら、、、
		if (IsAction != _next) {
			//Jump_MidAirの時は、速度上向きの間はアニメーションを切り替えない。
			if (IsAction == Define::rollAction_Basic::Jump_MidAir && playerStatus._y_speed <= 0)
				return;
			// アニメーションオブジェクトを更新し、終了。
			animation = switchingAnimation(_next);
			return;
		}
		
		// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
		// switchingAnimation()を実行せずに関数を終了。
		if (IsAction == Define::rollAction_Basic::Crouch || IsAction == Define::rollAction_Basic::Jump_MidAir)
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
@biref コントローラの入力状態によって次のアクション状態を取得する。playerStatusの更新はここでは行わない。状態を決定する処理だけ。
@date 2020/04/21/18:30
@author mimuro
*/
Define::rollAction_Basic Player::getNextAction(std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Animation> _animation)
{
	bool a = animation->isEnd();
	// Jump_Up to Jump_MidAir
	if (IsAction == Define::rollAction_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return Define::rollAction_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (IsAction == Define::rollAction_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return Define::rollAction_Basic::Fall;
	}

	// Jump_Landing
	if (IsAction == Define::rollAction_Basic::Fall	&& _collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
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
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus);
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
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, playerStatus, 3, 99, true);
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

