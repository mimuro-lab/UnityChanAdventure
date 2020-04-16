#include "ConfigScene.h"

void ConfigScene::update()
{
	changer->changeScene(eGameScene, true);
}

void ConfigScene::draw()
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "ConfigScene");
}