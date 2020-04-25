
/*!
@file Gamepad.cpp
@brief Gamepadクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/21/0:47
@author mimuro
*/

#include "Gamepad.h"
#include <DxLib.h>
#include "Keyboard.h"
#include "Define.h"
#include <string>
#include <algorithm>

using namespace std;

Gamepad::Gamepad()
{
    _idArray[static_cast<int>(ePad::down)] = 0;
    _idArray[static_cast<int>(ePad::left)] = 1;
    _idArray[static_cast<int>(ePad::right)] = 2;
    _idArray[static_cast<int>(ePad::up)] = 3;
    _idArray[static_cast<int>(ePad::maru)] = 5;
    _idArray[static_cast<int>(ePad::sankaku)] = 4;
    _idArray[static_cast<int>(ePad::sikaku)] = 7;
    _idArray[static_cast<int>(ePad::batu)] = 6;
    _idArray[static_cast<int>(ePad::select)] = 13;
    _idArray[static_cast<int>(ePad::start)] = 12;
}

void Gamepad::update()
{
    int padInput;
    padInput = GetJoypadInputState(DX_INPUT_PAD1);
    for (int i = 0; i < 16; i++) {
        if (padInput & (1 << i)) {
            _pad[i]++;
        }
        else {
            _pad[i] = 0;
        }
    }
}

/*!
@brief 渡されたパッドキー番号の入力フレーム数を返す
*/
int Gamepad::get(ePad eID) const
{
    return _pad[_idArray[static_cast<int>(eID)]];
}