
/*!
@file ConfigScene.cpp
@brief ConfigSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/19:53
@author mimuro
*/

#include "ConfigScene.h"

void ConfigScene::update()
{
	//changer->changeScene(eGameScene, true);
}

void ConfigScene::draw()
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "ConfigScene");
}