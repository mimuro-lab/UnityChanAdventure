
/*!
@file Controller.h
@brief Controllerクラスが定義されているヘッダファイル
@date 2020/04/18/20:14
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <vector>
#include "Keyboard.h"
#include "Gamepad.h"
#include "Singleton.h"

/*!
@class Controller
@brief ユーザからの入力情報を総括するクラス。
@date 2020/04/18/20:16
@author mimuro
*/
class Controller final:
	public Singleton<Controller>,
	private Keyboard,
	private Gamepad
{
	Controller() = default;
	friend Singleton< Controller >;
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
	//! スタートボタン入力状態
	bool push_start = false;
	bool on_start = false;
	//! セレクトボタン入力状態
	bool push_select = false;
	bool on_select = false;
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

public:

	//! 全ての入力状態を更新する。
	void update();
	//! 右方向ボタン入力状態の取得（押された瞬間）
	const bool getPushRight() { return push_right; }
	//! 左方向ボタン入力状態の取得（押された瞬間）
	const bool getPushLeft() { return push_left; }
	//! 上方向ボタン入力状態の取得（押された瞬間）
	const bool getPushUp() { return push_up; }
	//! 下方向ボタン入力状態の取得（押された瞬間）
	const bool getPushDown() { return push_down; }
	//! スタートボタン入力状態の取得（押された瞬間）
	const bool getPushStart() { return push_start; }
	//! セレクトボタン入力状態の取得（押された瞬間）
	const bool getPushSelect() { return push_select; }
	//! Ａ（〇）ボタン入力状態の取得（押された瞬間）
	const bool getPush_A() { return push_A; }	
	//! Ｂ（×）ボタン入力状態の取得（押された瞬間）
	const bool getPush_B() { return push_B; }	
	//! Ｘ（△）ボタン入力状態の取得（押された瞬間）
	const bool getPush_X() { return push_X; }	
	//! Ｙ（□）ボタン入力状態の取得（押された瞬間）
	const bool getPush_Y() { return push_Y; }	

	//! 右方向ボタン入力状態の取得（押された瞬間）
	const bool getOnRight() { return on_right; }
	//! 左方向ボタン入力状態の取得（押された瞬間）
	const bool getOnLeft() { return on_left; }
	//! 上方向ボタン入力状態の取得（押された瞬間）
	const bool getOnUp() { return on_up; }
	//! 下方向ボタン入力状態の取得（押された瞬間）
	const bool getOnDown() { return on_down; }
	//! スタートボタン入力状態の取得（押された瞬間）
	const bool getOnStart() { return on_start; }
	//! セレクトボタン入力状態の取得（押された瞬間）
	const bool getOnSelect() { return on_select; }
	//! Ａ（〇）ボタン入力状態の取得（押された瞬間）
	const bool getOn_A() { return on_A; }
	//! Ｂ（×）ボタン入力状態の取得（押された瞬間）
	const bool getOn_B() { return on_B; }
	//! Ｘ（△）ボタン入力状態の取得（押された瞬間）
	const bool getOn_X() { return on_X; }
	//! Ｙ（□）ボタン入力状態の取得（押された瞬間）
	const bool getOn_Y() { return on_Y; }

};

