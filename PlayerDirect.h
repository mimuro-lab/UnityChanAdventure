
/*!
@file PlayerDirect.h
@brief PlayerDirectクラスが定義されているヘッダファイル
@date 2020/05/04/17:43
@author mimuro
*/

#pragma once
#include "Define.h"
#include "Controller.h"

/*!
@class PlayerDirect
@brief Playerキャラの方向を更新するクラス。
@date 2020/05/04/17:43
@author mimuro
*/
class PlayerDirect
{
public:
	PlayerDirect() = default;
	~PlayerDirect() = default;

	//! 更新処理を行う関数。
	bool updateDirect(Define::rollAction_Basic nowAction, bool nowDirectRight);
};