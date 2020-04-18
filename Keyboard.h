
/*!
@file Keyboard.h
@brief Keyboardクラスが定義されているヘッダファイル
@date 2020/04/16/20:04
@author mimuro
*/

#pragma once
#include <array>

/*!
@class Keyboard
@brief キーボードにアクセスし、キーボードの状態を入力方向のみで管理するクラス。
@date 2020/04/16/20:00
@author mimuro
*/
class Keyboard {

protected:
	//! 更新
	bool update();	
	
	//! keyCodeのキーが押されているフレーム数を取得
	int getPressingCount(int keyCode);

	//! keyCodeのキーが離されているフレーム数を取得
	int getReleasingCount(int keyCode);

private:
	//! キーボードのキー総数
	static const int KEY_NUM = 256;	

	//! 押されカウンタ
	std::array<int, KEY_NUM> _pressingCount;
	
	//! 離されカウンタ
	std::array<int, KEY_NUM> _releasingCount;
	
	//! keyCodeが有効なキー番号か問う
	bool isAvailableCode(int keyCode);
};