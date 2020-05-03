#include "PlayerDirect.h"

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