
/*!
@file GameScene.cpp
@brief GameSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/19:58
@author mimuro
*/

#include "GameScene.h"

void GameScene::update()
{
	counterUpdate();
	SelectScene();
	if(!imagePath::getIns()->unityChan_BasicActions.empty())
		DrawFormatString(100, 50, GetColor(255, 255, 255), "%s", imagePath::getIns()->unityChan_BasicActions[getCounter()].c_str());
}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
}

void GameScene::SelectScene()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_S) == 1) {
		changer->changeScene(eStartScene, false);
	}
}