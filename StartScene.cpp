
/*!
@file StartScene.cpp
@brief StartSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/20:01
@author mimuro
*/

#include "StartScene.h"

void StartScene::update()
{
	SelectScene();
}

void StartScene::draw()
{
	DrawFormatString(10, 70, GetColor(255, 255, 255), "StartScene");
}

void StartScene::SelectScene()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) == 1) {
		changer->changeScene(eConfigScene, false);
	}
	else if(Keyboard::getIns()->getPressingCount(KEY_INPUT_M) == 1) {
		changer->changeScene(eMenuScene, false);
	}
	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_G) == 1) {
		changer->changeScene(eGameScene, false);
	}
}