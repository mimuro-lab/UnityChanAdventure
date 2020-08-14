
/*!
@file GameScene.h
@brief GameSceneクラスが定義されているヘッダファイル
@date 2020/04/16/19:55
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include "ImagePath_Unitychan.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyLoad.h"
#include "Stage.h"
#include "PredictStageShift.h"
#include "AbsDamageObj.h"

using namespace std;

/*!
@class GameScene
@brief SystemLooperクラスで生成されるシーンクラスの一つでAbstractSceneを継承する。ゲーム画面を担当する。
@date 2020/04/16/19:56
@author mimuro
*/
class GameScene :
	public AbstractScene,
	private SelectWindow
{
	//! 背景のStageの処理を行うオブジェクト
	shared_ptr<Stage> stage;

	shared_ptr<PredictStageShift> predictStageShift;

	//! Playerの処理をになうオブジェクト
	shared_ptr<Player> player;

	vector<shared_ptr<Enemy>> enemys;

	shared_ptr<EnemyLoad> enemyLoad;
	
	//! 画面上のダメージ要素
	vector<shared_ptr<AbsDamageObj>> damageObjs;

	//! 敵が生成したダメージ要素
	vector<shared_ptr<AbsDamageObj>> dmgObjFromEnemy;

	int deffOfStageAndBottom = 0;

public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	GameScene(shared_ptr<ISceneChanger> _changer) :
		AbstractScene(_changer),
		SelectWindow(_changer),
		stage(make_shared<Stage>(Define::blockWidth, Define::blockHeight)),
		player(make_shared<Player>(stage)),
		predictStageShift(make_shared<PredictStageShift>())
	{

		enemyLoad = make_shared<EnemyLoad>();

		for (unsigned int i = 0; i < enemyLoad->getElements().size(); i++) {
			shared_ptr<Enemy> ene = make_shared<Enemy>(stage, enemyLoad->getElements()[i].x, enemyLoad->getElements()[i].y, enemyLoad->getElements()[i].hitPoint);
			enemys.push_back(ene);
		}
	};
	~GameScene() = default;

	//! ゲーム画面に必要な前処理を行う関数。
	void update() override;

	//! ゲーム画面の描画を行う関数。
	void draw() override;
};

