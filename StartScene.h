#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
class StartScene : public AbstractScene
{
public:
	StartScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) {};
	~StartScene() = default;

	//! メニュー画面に必要な前処理を行う関数。
	void update() override;

	//! メニュー画面の描画を行う関数。
	void draw()  override;
};

