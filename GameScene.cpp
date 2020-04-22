
/*!
@file GameScene.cpp
@brief GameSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/19:58
@author mimuro
*/

#include "GameScene.h"

void GameScene::update()
{
	
	ValidSelectWindow();
	counterUpdate();

	if (IsSelected())
		return;	
	
	// セレクトウィンドウが閉じた瞬間のみコントローラの更新を行う。この瞬間はコントローラのpush（押された瞬間の状態）は無視したい。
	if(IsSelectWindow_Closed())
		Controller::getIns()->update();
	
	// ステージ処理
	stage->update();

	// 必ずセレクトウィンドウが開かれていない事を前提とする。オブジェクトの参照エラーが出る。
	player->update();
}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	
	player->draw();

	stage->draw();

	SelectWindow::drawSelectWindow();

}
