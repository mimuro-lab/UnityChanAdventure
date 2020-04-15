
/*!
@file SystemOwner.h
@brief SystemOwnerクラスが定義されているヘッダファイル。
@date 2020/04/16/3:41
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include "Define.h"
#include "SystemLooper.h"
#include <memory>

using namespace std;

/*!
@class SystemOwner
@brief 初期化処理や終了処理全般を担うクラス
@date 2020/04/14/23:43
@author mimuro
*/

class SystemOwner
{
public:
	SystemOwner() = default;
	~SystemOwner() = default;

	//! 初期化処理を行う関数。
	bool initialize() const;
	
	//! 終了処理を行う関数。
	bool finalize() const;

	//! 実行の中心処理を担う関数。初期化処理が成功した場合で実行される。
	bool main() const;

};

