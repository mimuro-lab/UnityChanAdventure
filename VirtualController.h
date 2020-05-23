#pragma once

class VirtualController
{
public:
	VirtualController() = default;
	~VirtualController() = default;

	void clear();

	//! 右方向ボタン入力状態
	bool push_right = false;
	bool on_right = false;
	//! 左方向ボタン入力状態
	bool push_left = false;
	bool on_left = false;
	//! 上方向ボタン入力状態
	bool push_up = false;
	bool on_up = false;
	//! 下方向ボタン入力状態
	bool push_down = false;
	bool on_down = false;
	//! Ａ（〇）ボタン入力状態
	bool push_A = false;
	bool on_A = false;
	//! Ｂ（×）ボタン入力状態
	bool push_B = false;
	bool on_B = false;
	//! Ｘ（△）ボタン入力状態
	bool push_X = false;
	bool on_X = false;
	//! Ｙ（□）ボタン入力状態
	bool push_Y = false;
	bool on_Y = false;
};

