
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
	ValidSelectWindow();

	if (IsSelected())
		return;	

	// 必ずセレクトウィンドウが開かれていない事を前提とする。オブジェクトの参照エラーが出る。
	player->update();
}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	player->draw();

	SelectWindow::drawSelectWindow();

}
