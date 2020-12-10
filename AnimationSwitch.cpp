
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
	Status playerStatus,
	VirtualController controller)
{

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "damaging %d", playerStatus.isDamaging);
	soardCombContinue = getSoardComb(nowAction, animation, soardCombContinue, controller);

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "comb : %d", soardCombContinue);
	
	// アニメーションを切り替えてもよいなら、
	if (acceptSwitching(animation, nowAction)) 
	{
		// _nextへ次のシーンを取得する。
		nextAction = getNextAction(collision, animation, playerStatus, nowAction, controller);
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
bool AnimationSwitch::acceptSwitching(shared_ptr<Animation> animation, characterAction nowAction)
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
bool AnimationSwitch::acceptNextAction(characterAction nowAction, characterAction nextAction, Status _playerStatus)
{
	// 現在のアクションと同じアクションが次のアクションだったら切り替えない。
	if (nowAction == nextAction)
		return false;

	//Jump_MidAirの時、かつ、速度上向きの間はアニメーションを切り替えない。
	if (nowAction == characterAction::Jump_MidAir && playerStatus._y_speed < 0)
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
bool AnimationSwitch::isRefresh(characterAction nowAction, shared_ptr<Animation> animation)
{
	// 途中切り替えＮＧかつアニメーションが終了したら、さらに、同じアクションが入力され続けて、Crouch（しゃがむ）だったら、、、
	// switchingAnimation()を実行せずに関数を終了。(refreshせずに終了)
	if (nowAction == characterAction::Crouch )
		return false;
	
	if (nowAction == characterAction::Jump_MidAir)
		return false;

	// 同じアクションが入力され続けて、現在のアニメーションが終了したら現在のアニメーションをリフレッシュする。
	// また、次のコマでの上記の処理"_next = getNextAction();"で再度その状態が更新される。
	if (!animation->isEnd())
		return false;

	// 上記の条件に当てはまらないのならリフレッシュする。
	return true;
}

bool AnimationSwitch::getSoardComb(characterAction nowAction, shared_ptr<Animation> animation, bool nowCombContinue, VirtualController controller)
{
	if (controller.push_X) {
		if (nowAction == characterAction::Soard1_init)
			return true;
		if (nowAction == characterAction::Soard2_init)
			return true;
		if (nowAction == characterAction::Soard3_init)
			return true;
	}


	return nowCombContinue;
}

/*!
@biref コントローラの入力状態によって次のアクション状態を取得する。playerStatusの更新はここでは行わない。状態を決定する処理だけ。
@date 2020/05/04/15:49
@author mimuro
*/
characterAction AnimationSwitch::getNextAction(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus,
	characterAction nowAction
	, VirtualController controller)
{

	if (playerStatus.isDead) {
		return characterAction::Death;
	}

	if (playerStatus.isDamage) {
		return characterAction::Damage;
	}

	// Brakeが終わったら強制的にアイドリング状態に変更する
	if (nowAction == characterAction::Brake && animation->isEnd()) {
		return characterAction::Idle;
	}

	// Jump_Up to Jump_MidAir
	if (nowAction == characterAction::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return characterAction::Jump_MidAir;
	}

	// 剣攻撃１はじめ
	if (controller.push_X)
		return characterAction::Soard1_init;


	// 剣攻撃コンボ1
	if (nowAction == characterAction::Soard1_init && nowAction != characterAction::Death) {

		// コンボするなら、次のコンボを返す。
		if (soardCombContinue) {
			soardCombContinue = false;
			return characterAction::Soard2_init;

		}

		// コンボしないならsoardCombContinueをfalseにして終了描画
		return characterAction::Soard1_end;

	}

	// 剣攻撃コンボ2
	if (nowAction == characterAction::Soard2_init && nowAction != characterAction::Death) {

		// コンボするなら、次のコンボを返す。
		if (soardCombContinue) {
			soardCombContinue = false;
			return characterAction::Soard3_init;

		}

		// コンボを続けないなら終了描画
		return characterAction::Soard1_end;
	}

	// 剣攻撃コンボ3
	if (nowAction == characterAction::Soard3_init && nowAction != characterAction::Death) {

		// コンボするなら、次のコンボを返す。
		if (soardCombContinue) {
			soardCombContinue = false;
			return characterAction::Soard2_init;
		}

		// コンボを続けないなら終了描画
		return characterAction::Soard1_end;
	}

	// ハンドガンの撃ち続ける処理
	if (nowAction == characterAction::Hundgun_init || nowAction == characterAction::Hundgun_horizonal
		&& controller.on_Y) {
		return characterAction::Hundgun_horizonal;
	}

	// ハンドガンを打ち終える処理
	if (nowAction == characterAction::Hundgun_horizonal) {
		return characterAction::Hundgun_end;
	}
	// ハンドガン撃ち始め
	if (controller.on_Y)
		return characterAction::Hundgun_init;



	// Jump_MidAir to Fall
	if (nowAction == characterAction::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return characterAction::Fall;
	}

	// ジャンプ中に頭上に障壁があったらFallに強制変更
	if (nowAction == characterAction::Jump_Up || nowAction == characterAction::Jump_MidAir) {
		if(collision->getCollisionedSide().head)
			return characterAction::Fall;
	}

	if (playerStatus._y_speed > 0) {
		return characterAction::Fall;
	}

	// Jump_Landing
	if (nowAction == characterAction::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return characterAction::Jump_Landing;
	}

	// ジャンプで浮き上がっているとき以外で、足元に障壁が無ければFallに強制変更
	if (nowAction != characterAction::Jump_Up && nowAction != characterAction::Jump_MidAir) {
		if (!collision->getCollisionedSide().bottom) {
			return characterAction::Fall;
		}
	}

	// Crouchする条件は、足元が地面についている事
	if (controller.on_down && collision->getCollisionedSide().bottom) {
		return characterAction::Crouch;
	}

	// Brake
	if (nowAction == characterAction::Run) {
		// R
		if (playerStatus.directRight && !controller.on_right)
			return characterAction::Brake;
		// L
		if (!playerStatus.directRight && !controller.on_left)
			return characterAction::Brake;
	}

	// Jumpする条件は、足元が地面についている事
	if (controller.push_A && collision->getCollisionedSide().bottom) {
		return characterAction::Jump_Up;
	}


	/// 足元が地面についている状態で、ジャンプで地面をけり上げた瞬間出ない時
	if (collision->getCollisionedSide().bottom && nowAction != characterAction::Jump_Up) {

		// Run R
		if (controller.on_B && controller.on_right) {
			playerStatus.directRight = true;
			return characterAction::Run;
		}

		// Run L
		if (controller.on_B && controller.on_left) {
			playerStatus.directRight = false;
			return characterAction::Run;
		}

		// Walk R
		if (controller.on_right) {
			playerStatus.directRight = true;
			return characterAction::Walk;
		}

		// Walk L
		if (controller.on_left) {
			playerStatus.directRight = false;
			return characterAction::Walk;
		}
	}
	// 何も入力されなければIdling状態にする。
	if (nowAction != characterAction::Jump_Up && nowAction != characterAction::Jump_MidAir) {

		return characterAction::Idle;
	}

	return nowAction;

}

/*!
@brief IsActionを更新して、次のアクションのAnimation型のオブジェクトを返す。
@date 2020/05/04/15:49
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::switchingAnimation(characterAction next, Status nowStatus)
{
	using namespace std;
	switch (next) {
	case characterAction::Brake:
		nowAction = characterAction::Brake;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Brake, nowStatus);
		break;
	case characterAction::Crouch:
		nowAction = characterAction::Crouch;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Crouch, nowStatus);
		break;
	case characterAction::Death:
		nowAction = characterAction::Death;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Death, nowStatus, 0, 0, 18, 99, true);
		break;
	case characterAction::Damage:
		nowAction = characterAction::Damage;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Damage, nowStatus);
		break;
	case characterAction::Idle:
		nowAction = characterAction::Idle;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Idle, nowStatus);
		break;
	case characterAction::Jump_Fall:
		nowAction = characterAction::Jump_Fall;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case characterAction::Jump_Landing:
		nowAction = characterAction::Jump_Landing;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case characterAction::Jump_MidAir:
		nowAction = characterAction::Jump_MidAir;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_MidAir, nowStatus, 3);
		break;
	case characterAction::Jump_Up:
		nowAction = characterAction::Jump_Up;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case characterAction::Fall:
		nowAction = characterAction::Fall;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Fall, nowStatus);
		break;
	case characterAction::Run:
		nowAction = characterAction::Run;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Run, nowStatus);
		break;
	case characterAction::Walk:
		nowAction = characterAction::Walk;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Walk, nowStatus);
		break;
	case characterAction::Hundgun_init:
		nowAction = characterAction::Hundgun_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Hundgun_init, nowStatus, 0, -3, 1);
		break;
	case characterAction::Hundgun_end:
		nowAction = characterAction::Hundgun_end;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Hundgun_end, nowStatus, 0, -3, 5);
		break;
	case characterAction::Hundgun_horizonal:
		nowAction = characterAction::Hundgun_horizonal;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Hundgun_horizonal, nowStatus, 0, -3, 4);
		break;
	case characterAction::Soard1_init:
		nowAction = characterAction::Soard1_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard1_init, nowStatus, 0, -59, 5);
		break;
	case characterAction::Soard1_end:
		nowAction = characterAction::Soard1_end;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard1_end, nowStatus, 0, -59, 3);
		break;
	case characterAction::Soard2_init:
		nowAction = characterAction::Soard2_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard2_init, nowStatus, 0, -59, 4);
		break;
	case characterAction::Soard3_init:
		nowAction = characterAction::Soard3_init;
		return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Soard3_init, nowStatus, 0, -59, 4);
		break;
	}

	// エラー処理、何も選択されなかったら取り合えずアイドリング状態にする。
	return make_shared <Animation>(ImagePath_Unitychan::getIns()->unityChan_Idle, nowStatus);
}
