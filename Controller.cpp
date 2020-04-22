
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
		push_start = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_H) > 1 ||
		Gamepad::get(Gamepad::ePad::start) > 1) {
		push_start = false;
		on_start = true;
	}
	else{
		push_start = on_start = false;
	}
	
	// Selectボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_G) == 1 ||
		Gamepad::get(Gamepad::ePad::select) == 1) {
		push_select = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_G) > 1 ||
		Gamepad::get(Gamepad::ePad::select) > 1) {
		push_select = false;
		on_select = true;
	}
	else {
		push_select = on_select = false;
	}
	
	// Upボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_E) == 1 ||
		Gamepad::get(Gamepad::ePad::up) == 1) {
		push_up = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_E) > 1 ||
		Gamepad::get(Gamepad::ePad::up) > 1) {
		push_up = false;
		on_up = true;
	}else {
		push_up = on_up = false;
	}

	// Downボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_D) == 1 ||
		Gamepad::get(Gamepad::ePad::down) == 1) {
		push_down = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_D) > 1 ||
		Gamepad::get(Gamepad::ePad::down) > 1) {
		push_down = false;
		on_down = true;
	}
	else {
		push_down = on_down = false;
	}

	// Rightボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_F) == 1 ||
		Gamepad::get(Gamepad::ePad::right) == 1) {
		push_right = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_F) > 1 ||
		Gamepad::get(Gamepad::ePad::right) > 1) {
		push_right = false;
		on_right = true;
	}else {
		push_right = false;
		on_right = false;
	}

	// Leftボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_S) == 1 ||
		Gamepad::get(Gamepad::ePad::left) == 1) {
		push_left = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_S) > 1 ||
		Gamepad::get(Gamepad::ePad::left) > 1) {
		push_left = false;
		on_left = true;
	}else {
		push_left = on_left = false;
	}

	// Aボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_L) == 1 ||
		Gamepad::get(Gamepad::ePad::maru) == 1) {
		push_A = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_L) > 1 ||
		Gamepad::get(Gamepad::ePad::maru) > 1) {
		push_A = false;
		on_A = true;
	}
	else{
		push_A = on_A = false;
	}

	// Bボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_K) == 1 ||
		Gamepad::get(Gamepad::ePad::batu) == 1) {
		push_B = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_K) > 1 ||
		Gamepad::get(Gamepad::ePad::batu) > 1) {
		push_B = false;
		on_B = true;
	}
	else {
		push_B = on_B = false;
	}

	// Xボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_I) == 1 ||
		Gamepad::get(Gamepad::ePad::sankaku) == 1) {
		push_X = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_I) > 1 ||
		Gamepad::get(Gamepad::ePad::sankaku) > 1) {
		push_X = false;
		on_X = true;
	}
	else {
		push_X = on_X = false;
	}

	// Yボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_J) == 1 ||
		Gamepad::get(Gamepad::ePad::sikaku) == 1) {
		push_Y = true;
	}
	else if (Keyboard::getPressingCount(KEY_INPUT_J) > 1 ||
		Gamepad::get(Gamepad::ePad::sikaku) > 1) {
		push_Y = false;
		on_Y = true;
	}
	else {
		push_Y = on_Y = false;
	}

	/*動作確認用
	printfDx("push:%d%d%d%d%d%d%d%d%d%d on:%d%d%d%d%d%d%d%d%d%d\n"
		, push_left, push_right, push_up, push_down, push_A, push_B, push_X, push_Y, push_select, push_start
		, on_left, on_right, on_up, on_down, on_A, on_B, on_X, on_Y, on_select, on_start);
	//*/
}