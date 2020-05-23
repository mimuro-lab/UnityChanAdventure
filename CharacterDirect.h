
/*!
@file CharacterDirect.h
@brief CharacterDirectクラスが定義されているヘッダファイル
@date 2020/05/04/17:43
@author mimuro
*/

#pragma once
#include "Define.h"
#include "VirtualController.h"

/*!
@class CharacterDirect
@brief Playerキャラの方向を更新するクラス。
@date 2020/05/04/17:43
@author mimuro
*/
class CharacterDirect
{
public:
	CharacterDirect() = default;
	~CharacterDirect() = default;

	//! 更新処理を行う関数。
	bool updateDirect(Define::characterAction nowAction, bool nowDirectRight, Define::Status nowStatus, VirtualController _controller);
};