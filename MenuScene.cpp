
/*!
@file MenuScene.cpp
@brief MenuSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/03:02
@author mimuro
*/

#include "MenuScene.h"

void MenuScene::update()
{
	ValidSelectWindow();
	SelectScene();
}

void MenuScene::draw()
{
	DrawFormatString(10, 50, GetColor(255,255,255), "MenuScene");
}

void MenuScene::SelectScene()
{
}