#pragma once
#include <DxLib.h>
#include "Define.h"

/*!
@brief 初期化処理や終了処理全般を担うクラス
@date 2020/04/14/23:43
@author mimuro
*/

class SystemOwner
{
public:
	/*!
	@brief コンストラクタをdefault宣言する理由はhttp://www.linktracktool.com/cpp/default-ctor.html参照
	*/
	SystemOwner() = default;
	~SystemOwner() = default;
	bool initialize() const;
	bool finalize() const;

	bool main() const;

};

