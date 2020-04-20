#pragma once

#include "Singleton.h"
#include <array>

class Gamepad
{
	const static int PAD_KEY_NUM = 16;

	//! どのボタンがどのボタンに割り当たっているかを示す
	std::array<int, PAD_KEY_NUM> _idArray = { 0 };
	
	//! 16ボタンのpad入力状態格納
	std::array<int, PAD_KEY_NUM> _pad = { 0 };
protected:

	Gamepad();
	~Gamepad() = default;

	enum ePad {
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

	void update();

	//! eIDのボタンの入力状態を取得
	int get(ePad eID) const;
};

