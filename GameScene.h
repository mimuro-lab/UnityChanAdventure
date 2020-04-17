
/*!
@file GameScene.h
@brief GameSceneクラスが定義されているヘッダファイル
@date 2020/04/16/19:55
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include <DxLib.h>
#include "imagePath.h"

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
	//! スタート画面から次のシーンを選択する。
	void SelectScene();
public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	GameScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer), SelectWindow(_changer) {};
	~GameScene() = default;

	//! ゲーム画面に必要な前処理を行う関数。
	void update() override;

	//! ゲーム画面の描画を行う関数。
	void draw() override;
};

