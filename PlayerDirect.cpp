
/*!
@file PlayerDirect.cpp
@brief PlayerDirectクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/05/04/17:47
@author mimuro
*/

#include "PlayerDirect.h"

/*!
@brief アクション状態がrunかwalkの時のみ方向の変換を受け付けるようにする。
@date 2020/05/04/17:47
@author mimuro
*/
bool PlayerDirect::updateDirect(Define::unityChan_Basic nowAction, bool nowDirectRight, Define::Status nowStatus)
{
	// 今のアクション状態がwalkだったらコントローラの入力状態で向きを変える。
	if (nowAction == Define::unityChan_Basic::Walk ||
		nowAction == Define::unityChan_Basic::Run /*||
		nowAction == Define::unityChan_Basic::Jump_Up ||
		nowAction == Define::unityChan_Basic::Jump_MidAir ||
		nowAction == Define::unityChan_Basic::Jump_Fall ||
		nowAction == Define::unityChan_Basic::Fall*/
		) {
		if (Controller::getIns()->getOnRight())
			return true;
		if (Controller::getIns()->getOnLeft())
			return false;
	}

	if (nowAction == Define::unityChan_Basic::Jump_Up ||
		nowAction == Define::unityChan_Basic::Jump_MidAir ||
		nowAction == Define::unityChan_Basic::Jump_Fall ||
		nowAction == Define::unityChan_Basic::Fall) {
		if (nowStatus._x_speed > 0)
			return true;
		else if (nowStatus._x_speed < 0)
			return false;
		// x速度が0の時、コントローラの入力で判断する。
		if (Controller::getIns()->getOnRight())
			return true;
		if (Controller::getIns()->getOnLeft())
			return false;
	}

	// 上記の状態以外の時は現在の向きを維持する。
	return nowDirectRight;

}