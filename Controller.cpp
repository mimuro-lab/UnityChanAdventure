
/*!
@file Controller.cpp
@brief Controllerクラスのメンバ類の定義を行うCPPファイル
@date 2020/04/18/20:33
@author mimuro
*/

#include "Controller.h"

/*!
@brief 各入力状態を更新する。押されているときのみtrue、話されるとfalse。状態保持などはこのクラスではしない。
@date 2020/04/18/20:31
@author mimuro
*/
void Controller::update()
{
	Keyboard::update();
	
	Gamepad::update();

	// Sartボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_H) == 1 ||
		Gamepad::get(Gamepad::ePad::start) == 1) {
		start = true;
	}
	else {
		start = false;
	}
	
	// Selectボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_G) == 1 ||
		Gamepad::get(Gamepad::ePad::select) == 1) {
		select = true;
	}
	else {
		select = false;
	}
	
	// Upボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_E) == 1 ||
		Gamepad::get(Gamepad::ePad::up) == 1) {
		up = true;
	}
	else {
		up = false;
	}

	// Downボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_D) == 1 ||
		Gamepad::get(Gamepad::ePad::down) == 1) {
		down = true;
	}
	else {
		down = false;
	}

	// Rightボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_F) == 1 ||
		Gamepad::get(Gamepad::ePad::right) == 1) {
		right = true;
	}
	else {
		right = false;
	}

	// Leftボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_S) == 1 ||
		Gamepad::get(Gamepad::ePad::left) == 1) {
		left = true;
	}
	else {
		left = false;
	}

	// Aボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_L) == 1 ||
		Gamepad::get(Gamepad::ePad::maru) == 1) {
		push_A = true;
	}
	else {
		push_A = false;
	}

	// Bボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_K) == 1 ||
		Gamepad::get(Gamepad::ePad::batu) == 1) {
		push_B = true;
	}
	else {
		push_B = false;
	}

	// Xボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_I) == 1 ||
		Gamepad::get(Gamepad::ePad::sankaku) == 1) {
		push_X = true;
	}
	else {
		push_X = false;
	}

	// Yボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_J) == 1 ||
		Gamepad::get(Gamepad::ePad::sikaku) == 1) {
		push_Y = true;
	}
	else {
		push_Y = false;
	}

}