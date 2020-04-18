
/*!
@file CalcUtils.h
@brief CalcUtilsクラスが定義されているヘッダファイル
@date 2020/04/18/15:38
@author mimuro
*/

#pragma once

class CalcUtils final
{
public:
    CalcUtils() = delete;

    //! float型の変数の小数点以下を四捨五入する関数。
    static float roundPoint(float val, int point);
};