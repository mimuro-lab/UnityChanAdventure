
/*!
@file Menu.h
@brief Menuクラスが定義されているヘッダファイル
@date 2020/04/16/03:02
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
#include <memory>

using namespace std;

/*!
@class Menu
@brief SystemLooperクラスで生成されるシーンクラスの一つでAbstractSceneを継承する。メニュー画面を担当する。
@date 2020/04/16/03:02
@author mimuro
*/
class Menu : public AbstractScene
{
public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	Menu(shared_ptr<ISceneChanger> _changer)  : AbstractScene(_changer) {};
	~Menu() = default;

	//! メニュー画面に必要な前処理を行う関数。
	void update() override;

	//! メニュー画面の描画を行う関数。
	void draw()  override;
};

