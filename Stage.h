#pragma once

#include <vector>
#include <DxLib.h>
#include "Define.h"

class Stage
{
private:
	Define::BlockCell initCell;
	
	std::vector<std::vector<Define::BlockCell>> _stage;

	int pointLeftUp_x = 10;
	int pointLeftUp_y = 10;

	char blockXNum = 20;
	char blockYNum = 20;

	char blockWidth = 30;
	char blockHeight = 30;

public:

	Stage();
	~Stage() = default;

	void update();
	void draw();

	const std::vector<std::vector<Define::BlockCell>> const getStage() { return _stage; }

	const char const getPointLeftUpX() { return pointLeftUp_x; }
	const char const getPointLeftUpY() { return pointLeftUp_y; }
	const char const getBlockWidth() { return blockWidth; }
	const char const getBlockHeight() { return blockHeight; }

};
