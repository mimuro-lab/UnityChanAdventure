
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
bool PlayerDirect::updateDirect(Define::rollAction_Basic nowAction, bool nowDirectRight)
{
	// 今のアクション状態がwalkだったらコントローラの入力状態で向きを変える。
	if (nowAction == Define::rollAction_Basic::Walk || nowAction == Define::rollAction_Basic::Run) {
		if (Controller::getIns()->getOnRight())
			return true;
		if (Controller::getIns()->getOnLeft())
			return false;
	}

	// 上記の状態以外の時は現在の向きを維持する。
	return nowDirectRight;

}