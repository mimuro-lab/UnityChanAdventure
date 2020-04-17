
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
	
	if (Controller::getIns()->getPush_A()) {
		changer->changeScene(eConfigScene, false);
	}
	else if(Controller::getIns()->getPush_B()) {
		changer->changeScene(eMenuScene, false);
	}
	else if (Controller::getIns()->getPush_X()) {
		changer->changeScene(eGameScene, false);
	}
	
}