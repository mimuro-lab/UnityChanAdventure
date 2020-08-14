
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
	player->update(stage, dmgObjFromEnemy);	

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


	// 無駄なダメージ要素の消去
	vector<shared_ptr<AbsDamageObj>> refreshedObjs;
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		if (damageObjs[i]->getIsLive())
			refreshedObjs.push_back(damageObjs[i]);
	}

	damageObjs = refreshedObjs;

	// 敵オブジェクトの更新
	for (unsigned int i = 0; i < enemys.size(); i++) {
		//enemys[i]->adjustBottom(deffOfStageAndBottom);
		enemys[i]->update(stage, shiftingStage, damageObjs);
		vector<shared_ptr<AbsDamageObj>> addDmg;
		addDmg = enemys[i]->generateDamageObj(addDmg, stage);
		for (unsigned int j = 0; j < addDmg.size(); j++) {
			dmgObjFromEnemy.push_back(addDmg[j]);
		}
	}

	// 敵が生成した攻撃要素を更新
	for (unsigned int i = 0; i < dmgObjFromEnemy.size(); i++) {
		dmgObjFromEnemy[i]->update(stage, shiftingStage, player->getStatus());
	}
	// 無駄な攻撃要素の削除
	vector<shared_ptr<AbsDamageObj>> deletedDmg;
	for (unsigned int i = 0; i < dmgObjFromEnemy.size(); i++) {
		if (dmgObjFromEnemy[i]->getIsLive())
			deletedDmg.push_back(dmgObjFromEnemy[i]);
	}
	dmgObjFromEnemy = deletedDmg;


	//// 敵オブジェクトにぶつかったダメージ要素は削除
	vector<shared_ptr<AbsDamageObj>> nonDetectEnemyDmgs;// 消去後のダメージ要素
	vector<int> deleteInd;// 削除対象のインデックスを格納する変数
	// 削除対象のインデックスを抽出する。
	for (unsigned int i = 0; i < enemys.size(); i++)
	{
		for (unsigned int j = 0; j < enemys[i]->getDetectedDamagesIndex().size(); j++) {
			deleteInd.push_back(enemys[i]->getDetectedDamagesIndex()[j]);
		}
	}
	sort(deleteInd.begin(), deleteInd.end());
	deleteInd.erase(std::unique(deleteInd.begin(), deleteInd.end()), deleteInd.end());
	// インデックスのダメージ要素にぶつかった処理を行わせる。
	for (unsigned int i = 0; i < deleteInd.size(); i++) {
		damageObjs[deleteInd[i]]->detectEnemy();
	}

	//// プレイヤーにぶつかったダメージ要素（敵が生成したもの）は削除
	vector<shared_ptr<AbsDamageObj>> nonDetectEnemyDmgsFromEnemy;// 消去後のダメージ要素
	vector<int> deleteIndFromEnemy;// 削除対象のインデックスを格納する変数
	// 削除対象のインデックスを抽出する。
	for (unsigned int j = 0; j < player->getDetectedDamagesIndex().size(); j++) {
		deleteIndFromEnemy.push_back(player->getDetectedDamagesIndex()[j]);
	}
	sort(deleteIndFromEnemy.begin(), deleteIndFromEnemy.end());
	deleteIndFromEnemy.erase(std::unique(deleteIndFromEnemy.begin(), deleteIndFromEnemy.end()), deleteIndFromEnemy.end());
	// インデックスのダメージ要素にぶつかった処理を行わせる。
	for (unsigned int i = 0; i < deleteIndFromEnemy.size(); i++) {
		dmgObjFromEnemy[deleteIndFromEnemy[i]]->detectPlayer();
	}

}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	
	stage->draw();

	for (unsigned int i = 0; i < enemys.size(); i++) {
		if(enemys[i]->getStatusAsParameter()->isActive)
			enemys[i]->draw();
	}

	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		//if (damageObjs[i]->getIsLive())
			damageObjs[i]->draw();
	}
	
	for (unsigned int i = 0; i < dmgObjFromEnemy.size();i++) {
		dmgObjFromEnemy[i]->draw();
	}

	player->draw();
	
	SelectWindow::drawSelectWindow();
}
