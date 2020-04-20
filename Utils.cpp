
/*!
@file Utils.cpp
@brief Utilsクラスのメンバ類の定義を行うCPPファイル
@date 2020/04/18/15:38\
@author mimuro
*/

#include "Utils.h"
#include <cmath>
#include <DxLib.h>

/*!
@brief  valの小数点第point位を四捨五入して丸める。
@date 2020/04/18/15:41
@author mimuro
*/
float Utils::roundPoint(float val, int point) {
    float ret;
    ret = val * pow(10.f, +point - 1);
    ret = (float)(int)(ret + 0.5f);
    return ret * pow(10.f, -point + 1);
}