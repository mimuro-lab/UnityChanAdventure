
/*!
@file GameScene.cpp
@brief GameSceneクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/16/19:58
@author mimuro
*/

#include "GameScene.h"

/*!
@brief プレイヤーオブジェクトの座標更新、アニメーションの処理などを行う。
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

	player->pushPlayerFromStage(stage);
	
	// playerによるダメージ要素の生成
	damageObjs = player->generateDamageObj(damageObjs,stage);

	// ダメージ要素の更新。
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		damageObjs[i]->update(stage, player->getShiftingState(), player->getStatus());
	}
	
	vector<shared_ptr<AbsDamageObj>> refreshedObjs;
	
	// 無駄なダメージ要素の消去
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		if (damageObjs[i]->getIsLive())
			refreshedObjs.push_back(damageObjs[i]);
	}

	damageObjs = refreshedObjs;

	for (unsigned int i = 0; i < enemys.size(); i++) {
		enemys[i]->update(stage, player->getShiftingState(), damageObjs);
	}


	
}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	
	player->draw();

	//enemy->draw();
	//enemy1->draw();

	stage->draw();

	for (unsigned int i = 0; i < enemys.size(); i++) {
		if(enemys[i]->getStatusAsParameter()->isActive)
			enemys[i]->draw();
	}

	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		//if (damageObjs[i]->getIsLive())
			damageObjs[i]->draw();
	}

	SelectWindow::drawSelectWindow();
}
