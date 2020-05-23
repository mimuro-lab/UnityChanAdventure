#include "VirtualController.h"

void VirtualController::clear()
{

	//! 右方向ボタン入力状態
	push_right = false;
	on_right = false;
	//! 左方向ボタン入力状態
	push_left = false;
	on_left = false;
	//! 上方向ボタン入力状態
	push_up = false;
	on_up = false;
	//! 下方向ボタン入力状態
	push_down = false;
	on_down = false;
	//! Ａ（〇）ボタン入力状態
	push_A = false;
	on_A = false;
	//! Ｂ（×）ボタン入力状態
	push_B = false;
	on_B = false;
	//! Ｘ（△）ボタン入力状態
	push_X = false;
	on_X = false;
	//! Ｙ（□）ボタン入力状態
	push_Y = false;
	on_Y = false;
}