
/*!
@file AnimationSwitch.cpp
@brief AnimationSwitchクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/05/04/15:29
@author mimuro
*/

#include "AnimationSwitch.h"

/*!
@brief コントローラやアニメーション、ステータスや当たり判定の状態から次のアクション状態を計算する。
@par 返すのはAnimation型の変数。
@date 2020/05/04/15:30
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::update(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus)
{

	// アニメーションを切り替えてもよいなら、
	if (acceptSwitching(animation, nowAction)) 
	{
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
			shared_ptr<Animation> returnAnimation = animation;
			returnAnimation->refreshing();
			return returnAnimation;
		}
	}

	return animation;

}

/*!
@brief アニメーションを切り替えても良いかを判断する。
@par アニメーションが終了する前に切り替えてもよい状態か、そうでなくてもアニメーションが終了した時にtrueを返す。
@date 2020/05/04/15:30
@author mimuro
*/
bool AnimationSwitch::acceptSwitching(shared_ptr<Animation> animation, rollAction_Basic nowAction)
{
	// 今の状態が途中切り替えＯＫだったら切り替えＯＫ
	if (IsAction_canSwitching[static_cast<int>(nowAction)])
		return true;

	// 途中切り替えＮＧかつアニメーションが終了したら切り替えＯＫ
	if(!IsAction_canSwitching[static_cast<int>(nowAction)] && animation->isEnd())
		return true;

	return false;
}

/*!
@brief 次の状態を受け入れてよいかどうかを判断する。
@par 次の状態が今と同じだったら継続なので切り替え処理を行わない。また、Jump_MidAirでは速度が上向きの時は切り替え処理を行わない。
@date 2020/05/04/15:43
@author mimuro
*/
bool AnimationSwitch::acceptNextAction(rollAction_Basic nowAction, rollAction_Basic nextAction, Status _playerStatus)
{
	// 現在のアクションと同じアクションが次のアクションだったら切り替えない。
	if (nowAction == nextAction)
		return false;

	//Jump_MidAirの時は、速度上向きの間はアニメーションを切り替えない。
	if (nowAction == rollAction_Basic::Jump_MidAir && playerStatus._y_speed < 0)
		return false;

	// 上記の条件に当てはまらないのなら切り替える。
	return true;
}

/*!
@brief アニメーションをリフレッシュするかどうか判断する関数。
@par しゃがむ・ジャンプ（空中）、アニメーションが終了していないならリフレッシュしない。それ以外ならリフレッシュする。
@date 2020/05/04/15:48
@author mimuro
*/
bool AnimationSwitch::isRefresh(rollAction_Basic nowAction, shared_ptr<Animation> animation)
{
	// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
	// switchingAnimation()を実行せずに関数を終了。(refreshせずに終了)
	if (nowAction == rollAction_Basic::Crouch )
		return false;
	
	if (nowAction == rollAction_Basic::Jump_MidAir)
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
@date 2020/05/04/15:49
@author mimuro
*/
rollAction_Basic AnimationSwitch::getNextAction(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus,
	rollAction_Basic nowAction)
{

	// Brakeが終わったら強制的にアイドリング状態に変更する
	if (nowAction == rollAction_Basic::Brake && animation->isEnd()) {
		return rollAction_Basic::Idle;
	}

	// Jump_Up to Jump_MidAir
	if (nowAction == rollAction_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return rollAction_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (nowAction == rollAction_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return rollAction_Basic::Fall;
	}

	// ジャンプ中に頭上に障壁があったらFallに強制変更
	if (nowAction == rollAction_Basic::Jump_Up || nowAction == rollAction_Basic::Jump_MidAir) {
		if(collision->getCollisionedSide().head)
			return rollAction_Basic::Jump_Fall;
	}

	// Jump_Landing
	if (nowAction == rollAction_Basic::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return rollAction_Basic::Jump_Landing;
	}

	// ジャンプで浮き上がっているとき以外で、足元に障壁が無ければFallに強制変更
	if (nowAction != rollAction_Basic::Jump_Up && nowAction != rollAction_Basic::Jump_MidAir) {
		if (!collision->getCollisionedSide().bottom) {
			return rollAction_Basic::Fall;
		}
	}

	// Crouchする条件は、足元が地面についている事
	if (Controller::getIns()->getOnDown() && collision->getCollisionedSide().bottom) {
		return rollAction_Basic::Crouch;
	}

	// Brake
	if (nowAction == rollAction_Basic::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return rollAction_Basic::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft())
			return rollAction_Basic::Brake;
	}

	// Jumpする条件は、足元が地面についている事
	if (Controller::getIns()->getPush_A() && collision->getCollisionedSide().bottom) {
		return rollAction_Basic::Jump_Up;
	}

	/// 足元が地面についている状態で、ジャンプで地面をけり上げた瞬間出ない時
	if (collision->getCollisionedSide().bottom && nowAction != rollAction_Basic::Jump_Up) {
		// Run R
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return rollAction_Basic::Run;
		}

		// Run L
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return rollAction_Basic::Run;
		}

		// Walk R
		if (Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return rollAction_Basic::Walk;
		}

		// Walk L
		if (Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return rollAction_Basic::Walk;
		}
	}
	// 何も入力されなければIdling状態にする。

	if(nowAction != rollAction_Basic::Jump_Up && nowAction != rollAction_Basic::Jump_MidAir)
		return rollAction_Basic::Idle;

	return nowAction;

}

/*!
@brief IsActionを更新して、次のアクションのAnimation型のオブジェクトを返す。
@date 2020/05/04/15:49
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::switchingAnimation(rollAction_Basic next, Status nowStatus)
{
	using namespace std;
	switch (next) {
	case rollAction_Basic::Brake:
		nowAction = rollAction_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, nowStatus);
		break;
	case rollAction_Basic::Crouch:
		nowAction = rollAction_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, nowStatus);
		break;
	case rollAction_Basic::Damage:
		nowAction = rollAction_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, nowStatus);
		break;
	case rollAction_Basic::Idle:
		nowAction = rollAction_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
		break;
	case rollAction_Basic::Jump_Fall:
		nowAction = rollAction_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case rollAction_Basic::Jump_Landing:
		nowAction = rollAction_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case rollAction_Basic::Jump_MidAir:
		nowAction = rollAction_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, nowStatus, 3, 99, true);
		break;
	case rollAction_Basic::Jump_Up:
		nowAction = rollAction_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case rollAction_Basic::Fall:
		nowAction = rollAction_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, nowStatus);
		break;
	case rollAction_Basic::Run:
		nowAction = rollAction_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, nowStatus);
		break;
	case rollAction_Basic::Walk:
		nowAction = rollAction_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, nowStatus);
		break;
	}

	// エラー処理、何も選択されなかったら取り合えずアイドリング状態にする。
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
}
