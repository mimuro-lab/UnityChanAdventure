
/*!
@file ConfigScene.cpp
@brief ConfigSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/19:53
@author mimuro
*/

#include "ConfigScene.h"

void ConfigScene::update()
{
	SelectWindow::ValidSelectWindow();
	SelectScene();
}

void ConfigScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "ConfigScene");
	SelectWindow::drawSelectWindow();
}

void ConfigScene::SelectScene()
{
}