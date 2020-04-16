#pragma once

#include "AbstractScene.h"
#include <DxLib.h>

class GameScene :
	public AbstractScene
{
public:
	GameScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) {};
	~GameScene() = default;

	void update() override;
	void draw() override;
};

