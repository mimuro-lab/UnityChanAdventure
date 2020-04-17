
/*!
@file StartScene.h
@brief StartSceneクラスが定義されているヘッダファイル
@date 2020/04/16/20:00
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include "Controller.h"
#include <DxLib.h>

/*!
@class StartScene
@brief SystemLooperクラスで生成されるシーンクラスの一つでAbstractSceneを継承する。スタート画面を担当する。
@date 2020/04/16/20:00
@author mimuro
*/
class StartScene : public AbstractScene
{
	//! スタート画面から次のシーンを選択する。変数nextSceneSelectedを更新する。
	const void SelectScene();

	enum nextScene {
		none,
		game,
		menu,
		config,
		_end,
	};

	char nextSceneSelected = 0;

	//! 選択したシーンへ移動する。
	const void GoNextScene();

public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	StartScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) {};
	~StartScene() = default;

	//! メニュー画面に必要な前処理を行う関数。
	void update() override;

	//! メニュー画面の描画を行う関数。
	void draw()  override;
};

