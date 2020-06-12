
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

	Dimention shiftingStage = predictStageShift->update(stage, player, player->getShiftingState());

	// ステージ処理
	stage->update(shiftingStage, player->getStatus());

	// プレイヤーの底がめり込んでいたら発動（０以外の値を返す）
	deffOfStageAndBottom = player->adjustStageAndBottom(stage);

	//adjustがついている関数はプレイヤーがめり込んだ際の「押し出し」に関する処理

	//stage->adjustBottom(deffOfStageAndBottom);

	//player->adjustStageAndBottom(stage);
	
	// playerによるダメージ要素の生成
	damageObjs = player->generateDamageObj(damageObjs,stage);

	// ダメージ要素の更新。
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		//damageObjs[i]->adjustBottom(deffOfStageAndBottom);
		damageObjs[i]->update(stage, shiftingStage, player->getStatus());
	}
	
	vector<shared_ptr<AbsDamageObj>> refreshedObjs;
	
	// 無駄なダメージ要素の消去
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		if (damageObjs[i]->getIsLive())
			refreshedObjs.push_back(damageObjs[i]);
	}

	damageObjs = refreshedObjs;

	for (unsigned int i = 0; i < enemys.size(); i++) {
		//enemys[i]->adjustBottom(deffOfStageAndBottom);
		enemys[i]->update(stage, shiftingStage, damageObjs);
		
	}
	
}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	
	player->draw();

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
