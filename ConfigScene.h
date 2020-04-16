#pragma once
#include "AbstractScene.h"
#include <DxLib.h>

class ConfigScene : public AbstractScene
{
public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	ConfigScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) {};
	~ConfigScene() = default;

	//! メニュー画面に必要な前処理を行う関数。
	void update() override;

	//! メニュー画面の描画を行う関数。
	void draw()  override;
};

