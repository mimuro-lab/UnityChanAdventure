#include "Controller.h"

void Controller::update()
{
	Keyboard::update();
	
	// Sartボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_SPACE) == 1) {
		start = !start;
	}   
	
	// Selectボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_LSHIFT) == 1) {
		select = !select;
	}
	
	// Upボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_E) == 1) {
		up = true;
	}
	else {
		up = false;
	}

	// Downボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_D) == 1) {
		down = true;
	}
	else {
		down = true;
	}

	// Rightボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_F) == 1) {
		right = true;
	}
	else {
		right = false;
	}

	// Leftボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_S) == 1) {
		left = true;
	}
	else {
		left = false;
	}

	// Aボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_L) == 1) {
		push_A = true;
	}
	else {
		push_A = false;
	}

	// Bボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_K) == 1) {
		push_B = true;
	}
	else {
		push_B = false;
	}

	// Xボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_I) == 1) {
		push_X = true;
	}
	else {
		push_X = false;
	}

	// Yボタンの更新
	if (Keyboard::getPressingCount(KEY_INPUT_J) == 1) {
		push_Y = true;
	}
	else {
		push_Y = false;
	}

}