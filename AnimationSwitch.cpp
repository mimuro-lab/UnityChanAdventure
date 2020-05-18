
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

	soardCombContinue = getSoardComb(nowAction, animation, soardCombContinue);

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "comb : %d", soardCombContinue);
	
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
bool AnimationSwitch::acceptSwitching(shared_ptr<Animation> animation, unityChan_Basic nowAction)
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
bool AnimationSwitch::acceptNextAction(unityChan_Basic nowAction, unityChan_Basic nextAction, Status _playerStatus)
{
	// 現在のアクションと同じアクションが次のアクションだったら切り替えない。
	if (nowAction == nextAction)
		return false;

	//Jump_MidAirの時は、速度上向きの間はアニメーションを切り替えない。
	if (nowAction == unityChan_Basic::Jump_MidAir && playerStatus._y_speed < 0)
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
bool AnimationSwitch::isRefresh(unityChan_Basic nowAction, shared_ptr<Animation> animation)
{
	// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
	// switchingAnimation()を実行せずに関数を終了。(refreshせずに終了)
	if (nowAction == unityChan_Basic::Crouch )
		return false;
	
	if (nowAction == unityChan_Basic::Jump_MidAir)
		return false;

	// 同じアクションが入力され続けて、現在のアニメーションが終了したら現在のアニメーションをリフレッシュする。
	// また、次のコマでの上記の処理"_next = getNextAction();"で再度その状態が更新される。
	if (!animation->isEnd())
		return false;

	// 上記の条件に当てはまらないのならリフレッシュする。
	return true;
}

bool AnimationSwitch::getSoardComb(unityChan_Basic nowAction, shared_ptr<Animation> animation, bool nowCombContinue)
{
	if (Controller::getIns()->getPush_X()) {
		if (nowAction == unityChan_Basic::Soard1_init)
			return true;
		if (nowAction == unityChan_Basic::Soard2_init)
			return true;
		if (nowAction == unityChan_Basic::Soard3_init)
			return true;
	}


	return nowCombContinue;
}

/*!
@biref コントローラの入力状態によって次のアクション状態を取得する。playerStatusの更新はここでは行わない。状態を決定する処理だけ。
@date 2020/05/04/15:49
@author mimuro
*/
unityChan_Basic AnimationSwitch::getNextAction(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus,
	unityChan_Basic nowAction)
{

	// Brakeが終わったら強制的にアイドリング状態に変更する
	if (nowAction == unityChan_Basic::Brake && animation->isEnd()) {
		return unityChan_Basic::Idle;
	}

	// Jump_Up to Jump_MidAir
	if (nowAction == unityChan_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return unityChan_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (nowAction == unityChan_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return unityChan_Basic::Fall;
	}

	// ジャンプ中に頭上に障壁があったらFallに強制変更
	if (nowAction == unityChan_Basic::Jump_Up || nowAction == unityChan_Basic::Jump_MidAir) {
		if(collision->getCollisionedSide().head)
			return unityChan_Basic::Jump_Fall;
	}

	// Jump_Landing
	if (nowAction == unityChan_Basic::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return unityChan_Basic::Jump_Landing;
	}

	// ジャンプで浮き上がっているとき以外で、足元に障壁が無ければFallに強制変更
	if (nowAction != unityChan_Basic::Jump_Up && nowAction != unityChan_Basic::Jump_MidAir) {
		if (!collision->getCollisionedSide().bottom) {
			return unityChan_Basic::Fall;
		}
	}

	// Crouchする条件は、足元が地面についている事
	if (Controller::getIns()->getOnDown() && collision->getCollisionedSide().bottom) {
		return unityChan_Basic::Crouch;
	}

	// Brake
	if (nowAction == unityChan_Basic::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return unityChan_Basic::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft())
			return unityChan_Basic::Brake;
	}

	// Jumpする条件は、足元が地面についている事
	if (Controller::getIns()->getPush_A() && collision->getCollisionedSide().bottom) {
		return unityChan_Basic::Jump_Up;
	}

	// 剣攻撃コンボ1
	if (nowAction == unityChan_Basic::Soard1_init) {

		// コンボするなら、次のコンボを返す。
		if (soardCombContinue) {
			soardCombContinue = false;
			return unityChan_Basic::Soard2_init;
			
		}

		// コンボしないならsoardCombContinueをfalseにして終了描画
		return unityChan_Basic::Soard1_end;

	}

	// 剣攻撃コンボ2
	if (nowAction == unityChan_Basic::Soard2_init) {

		// コンボするなら、次のコンボを返す。
		if (soardCombContinue) {
			soardCombContinue = false;
			return unityChan_Basic::Soard3_init;

		}

		// コンボを続けないなら終了描画
		return unityChan_Basic::Soard1_end;
	}

	// 剣攻撃コンボ3
	if (nowAction == unityChan_Basic::Soard3_init) {

		// コンボするなら、次のコンボを返す。
		if (soardCombContinue) {
			soardCombContinue = false;
			return unityChan_Basic::Soard1_init;
		}

		// コンボを続けないなら終了描画
		return unityChan_Basic::Soard1_end;
	}

	// ハンドガンの撃ち続ける処理
	if (nowAction == unityChan_Basic::Hundgun_init || nowAction==unityChan_Basic::Hundgun_horizonal
		&& Controller::getIns()->getOn_Y()) {
		return unityChan_Basic::Hundgun_horizonal;
	}

	// ハンドガンを打ち終える処理
	if (nowAction == unityChan_Basic::Hundgun_horizonal) {
		return unityChan_Basic::Hundgun_end;
	}

	/// 足元が地面についている状態で、ジャンプで地面をけり上げた瞬間出ない時
	if (collision->getCollisionedSide().bottom && nowAction != unityChan_Basic::Jump_Up) {

		// 剣攻撃１はじめ
		if (Controller::getIns()->getOn_X())
			return unityChan_Basic::Soard1_init;

		// ハンドガン撃ち始め
		if (Controller::getIns()->getOn_Y())
			return unityChan_Basic::Hundgun_init;

		// Run R
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return unityChan_Basic::Run;
		}

		// Run L
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return unityChan_Basic::Run;
		}

		// Walk R
		if (Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return unityChan_Basic::Walk;
		}

		// Walk L
		if (Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return unityChan_Basic::Walk;
		}
	}

	// 何も入力されなければIdling状態にする。
	if (nowAction != unityChan_Basic::Jump_Up && nowAction != unityChan_Basic::Jump_MidAir) {

		return unityChan_Basic::Idle;
	}

	return nowAction;

}

/*!
@brief IsActionを更新して、次のアクションのAnimation型のオブジェクトを返す。
@date 2020/05/04/15:49
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::switchingAnimation(unityChan_Basic next, Status nowStatus)
{
	using namespace std;
	switch (next) {
	case unityChan_Basic::Brake:
		nowAction = unityChan_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, nowStatus);
		break;
	case unityChan_Basic::Crouch:
		nowAction = unityChan_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, nowStatus);
		break;
	case unityChan_Basic::Damage:
		nowAction = unityChan_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, nowStatus);
		break;
	case unityChan_Basic::Idle:
		nowAction = unityChan_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
		break;
	case unityChan_Basic::Jump_Fall:
		nowAction = unityChan_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case unityChan_Basic::Jump_Landing:
		nowAction = unityChan_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case unityChan_Basic::Jump_MidAir:
		nowAction = unityChan_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, nowStatus, 3);
		break;
	case unityChan_Basic::Jump_Up:
		nowAction = unityChan_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case unityChan_Basic::Fall:
		nowAction = unityChan_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, nowStatus);
		break;
	case unityChan_Basic::Run:
		nowAction = unityChan_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, nowStatus);
		break;
	case unityChan_Basic::Walk:
		nowAction = unityChan_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, nowStatus);
		break;
	case unityChan_Basic::Hundgun_init:
		nowAction = unityChan_Basic::Hundgun_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Hundgun_init, nowStatus, 0, -3, 3);
		break;
	case unityChan_Basic::Hundgun_end:
		nowAction = unityChan_Basic::Hundgun_end;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Hundgun_end, nowStatus, 0, -3, 5);
		break;
	case unityChan_Basic::Hundgun_horizonal:
		nowAction = unityChan_Basic::Hundgun_horizonal;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Hundgun_horizonal, nowStatus, 0, -3, 3);
		break;
	case unityChan_Basic::Soard1_init:
		nowAction = unityChan_Basic::Soard1_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard1_init, nowStatus, 0, -59, 3);
		break;
	case unityChan_Basic::Soard1_end:
		nowAction = unityChan_Basic::Soard1_end;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard1_end, nowStatus, 0, -59, 5);
		break;
	case unityChan_Basic::Soard2_init:
		nowAction = unityChan_Basic::Soard2_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard2_init, nowStatus, 0, -59, 3);
		break;
	case unityChan_Basic::Soard3_init:
		nowAction = unityChan_Basic::Soard3_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard3_init, nowStatus, 0, -59, 3);
		break;
	}

	// エラー処理、何も選択されなかったら取り合えずアイドリング状態にする。
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
}
