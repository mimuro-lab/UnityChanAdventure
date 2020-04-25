
/*!
@file Gamepad.h
@brief Gamepadクラスが定義されているヘッダファイル
@date 2020/04/21/0:44
@author mimuro
*/

#pragma once
#include "Singleton.h"
#include <array>

/*!
@class Gamepad
@brief ゲームコントローラ（PS3）にアクセスし、状態を入力方向のみで管理するクラス。
@date 2020/04/21/0:44
@author mimuro
*/
class Gamepad
{
	//! ゲームパッドのキー総数
	const static int PAD_KEY_NUM = 16;

	//! どのボタンがどのボタンに割り当たっているかを示す
	std::array<int, PAD_KEY_NUM> _idArray = { 0 };
	
	//! 16ボタンのpad入力状態格納
	std::array<int, PAD_KEY_NUM> _pad = { 0 };

protected:

	Gamepad();
	//! ゲームパッドの配置の定義
	enum class ePad {
		left,
		right,
		up,
		down,
		sikaku,
		maru,
		sankaku,
		batu,
		start,
		select
	};

	//! 更新
	void update();

	//! eIDのボタンの入力状態を取得
	int get(ePad eID) const;
};

