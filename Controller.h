
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
#include "Singleton.h"

/*!
@class Controller
@brief ユーザからの入力情報を総括するクラス。
@date 2020/04/18/20:16
@author mimuro
*/
class Controller final:
	public Singleton<Controller>,
	private Keyboard
{
	Controller() = default;
	friend Singleton< Controller >;
	//! 右方向ボタン入力状態
	bool right = false;
	//! 左方向ボタン入力状態
	bool left = false;
	//! 上方向ボタン入力状態
	bool up = false;
	//! 下方向ボタン入力状態
	bool down = false;
	//! スタートボタン入力状態
	bool start = false;
	//! セレクトボタン入力状態
	bool select = false;
	//! Ａ（〇）ボタン入力状態
	bool push_A = false;
	//! Ｂ（×）ボタン入力状態
	bool push_B = false;
	//! Ｘ（△）ボタン入力状態
	bool push_X = false;
	//! Ｙ（□）ボタン入力状態
	bool push_Y = false;

public:

	//! 全ての入力状態を更新する。
	void update();
	//! 右方向ボタン入力状態の取得
	const bool getRight() { return right; }		
	//! 左方向ボタン入力状態の取得
	const bool getLeft() { return left; }		
	//! 上方向ボタン入力状態の取得
	const bool getUp() { return up; }			
	//! 下方向ボタン入力状態の取得
	const bool getDown() { return down; }		
	//! スタートボタン入力状態の取得
	const bool getStart() { return start; }		
	//! セレクトボタン入力状態の取得
	const bool getSelect() { return select; }	
	//! Ａ（〇）ボタン入力状態の取得
	const bool getPush_A() { return push_A; }	
	//! Ｂ（×）ボタン入力状態の取得
	const bool getPush_B() { return push_B; }	
	//! Ｘ（△）ボタン入力状態の取得
	const bool getPush_X() { return push_X; }	
	//! Ｙ（□）ボタン入力状態の取得
	const bool getPush_Y() { return push_Y; }	

};

