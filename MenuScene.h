
/*!
@file MenuScene.h
@brief MenuSceneクラスが定義されているヘッダファイル
@date 2020/04/16/03:02
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include <DxLib.h>
#include <memory>

using namespace std;

/*!
@class MenuScene
@brief SystemLooperクラスで生成されるシーンクラスの一つでAbstractSceneを継承する。メニュー画面を担当する。
@date 2020/04/16/03:02
@author mimuro
*/
class MenuScene : public AbstractScene, private SelectWindow
{
	//! スタート画面から次のシーンを選択する。
	void SelectScene();

public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	MenuScene(shared_ptr<ISceneChanger> _changer)  : AbstractScene(_changer), SelectWindow(_changer) {};
	~MenuScene() = default;

	//! メニュー画面に必要な前処理を行う関数。
	void update() override;

	//! メニュー画面の描画を行う関数。
	void draw()  override;
};

