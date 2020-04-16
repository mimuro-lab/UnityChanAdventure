#include "GameScene.h"

void GameScene::update()
{
	changer->changeScene(eMenuScene, true);
}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
}