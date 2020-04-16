#include "Config.h"

void Config::update()
{
	changer->changeScene(eMenu, true);
}

void Config::draw()
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Config");
}