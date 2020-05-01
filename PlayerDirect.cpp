#include "PlayerDirect.h"

bool PlayerDirect::updateDirect(Define::rollAction_Basic nowAction, bool nowDirectRight)
{
	/*
	// 今のアクション状態がブレーキだったら向きを変えない。
	if (nowAction == Define::rollAction_Basic::Brake)
		return nowDirectRight;

	// 今のアクション状態がジャンプ中だったら向きを変えない。
	if (nowAction == Define::rollAction_Basic::Jump_Up ||
		nowAction == Define::rollAction_Basic::Jump_MidAir ||
		nowAction == Define::rollAction_Basic::Jump_Fall ||
		nowAction == Define::rollAction_Basic::Jump_Landing)
		return nowDirectRight;

	// 今のアクション状態がブレーキだったら向きを変えない。
	if (nowAction == Define::rollAction_Basic::Brake)
		return nowDirectRight;

	// 今のアクション状態がアイドリングだったら向きを変えない。
	if (nowAction == Define::rollAction_Basic::Idle)
		return nowDirectRight;
		*/
	// 今のアクション状態がwalkだったらコントローラの入力状態で向きを変える。
	if (nowAction == Define::rollAction_Basic::Walk) {
		if (Controller::getIns()->getOnRight())
			return true;
		if (Controller::getIns()->getOnLeft())
			return false;
	}

	// 上記の状態以外の時は現在の向きを維持する。
	return nowDirectRight;

}