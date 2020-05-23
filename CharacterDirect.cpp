
/*!
@file CharacterDirect.cpp
@brief CharacterDirectクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/05/04/17:47
@author mimuro
*/

#include "CharacterDirect.h"

/*!
@brief アクション状態がrunかwalkの時のみ方向の変換を受け付けるようにする。
@date 2020/05/04/17:47
@author mimuro
*/
bool CharacterDirect::updateDirect(Define::characterAction nowAction, bool nowDirectRight, Define::Status nowStatus, VirtualController controller)
{
	// 今のアクション状態がwalkだったらコントローラの入力状態で向きを変える。
	if (nowAction == Define::characterAction::Walk ||
		nowAction == Define::characterAction::Run /*||
		nowAction == Define::characterAction::Jump_Up ||
		nowAction == Define::characterAction::Jump_MidAir ||
		nowAction == Define::characterAction::Jump_Fall ||
		nowAction == Define::characterAction::Fall*/
		) {
		if (controller.on_right)
			return true;
		if (controller.on_left)
			return false;
	}

	if (nowAction == Define::characterAction::Jump_Up ||
		nowAction == Define::characterAction::Jump_MidAir ||
		nowAction == Define::characterAction::Jump_Fall ||
		nowAction == Define::characterAction::Fall) {
		if (nowStatus._x_speed > 0)
			return true;
		else if (nowStatus._x_speed < 0)
			return false;
		// x速度が0の時、コントローラの入力で判断する。
		if (controller.on_right)
			return true;
		if (controller.on_left)
			return false;
	}

	// 上記の状態以外の時は現在の向きを維持する。
	return nowDirectRight;

}