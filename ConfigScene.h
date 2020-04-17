
/*!
@file ConfigScene.h
@brief ConfigSceneクラスが定義されているヘッダファイル。
@date 2020/04/16/19:50
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include <DxLib.h>

/*!
@class ConfigScene
@brief SystemLooperクラスで生成されるシーンクラスの一つでAbstractSceneを継承する。設定画面を担当する。
@date 2020/04/16/19:52
@author mimuro
*/
class ConfigScene : public AbstractScene
	,private SelectWindow
{
	//! スタート画面から次のシーンを選択する。
	void SelectScene();
public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	ConfigScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) , SelectWindow(_changer){};
	~ConfigScene() = default;

	//! メニュー画面に必要な前処理を行う関数。
	void update() override;

	//! メニュー画面の描画を行う関数。
	void draw()  override;
};

