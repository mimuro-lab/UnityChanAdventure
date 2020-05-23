
/*!
@file GameScene.cpp
@brief GameSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/19:58
@author mimuro
*/

#include "GameScene.h"

/*!
@brief プレイヤーオブジェクトの座標更新、アニメーションの処理などを行う。nnnnnnnnnnn
@date 2020/04/21/12:36
@author mimuro
@callgraph
*/
void GameScene::update()
{
	
	ValidSelectWindow();
	counterUpdate();

	if (IsSelected())
		return;	
	
	// セレクトウィンドウが閉じた瞬間のみコントローラの更新を行う。この瞬間はコントローラのpush（押された瞬間の状態）は無視したい。
	if(IsSelectWindow_Closed())
		Controller::getIns()->update();

	

	// 必ずセレクトウィンドウが開かれていない事を前提とする。オブジェクトの参照エラーが出る。
	player->update(stage);	

	// ステージ処理
	stage->update(player->getShiftingState(), player->getStatus());
	
	enemy->update(stage, player->getShiftingState());

	enemy1->update(stage, player->getShiftingState());
	
	// playerによるダメージ要素の生成
	damageObjs = player->generateDamageObj(damageObjs);

	// ダメージ要素の更新。
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		damageObjs[i]->update(player->getShiftingState().x, player->getShiftingState().y);
	}

}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	
	player->draw();

	enemy->draw();
	enemy1->draw();

	stage->draw();

	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		damageObjs[i]->draw();
	}

	SelectWindow::drawSelectWindow();
}
