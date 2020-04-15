#pragma once
#include <DxLib.h>

/*!
@brief ループする処理の中心を担うクラス
@date 2020/04/15/15:12
@author mimuro
*/
class SystemLooper
{
public:
	SystemLooper() = default;
	~SystemLooper() = default;
	bool Error() const;
	bool scrProcess() const;
};

