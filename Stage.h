#pragma once

#include <vector>
#include <DxLib.h>
#include "Define.h"

class Stage
{
private:
	Define::BlockCell initCell;
	
	std::vector<std::vector<Define::BlockCell>> _stage;

	int pointLeftUp_x = 0;
	int pointLeftUp_y = 0;

	char blockXNum = 20;
	char blockYNum = 20;

public:
	
	unsigned char blockWidth;
	unsigned char blockHeight;

	Stage(unsigned char blockWidth, unsigned char blockHeight);
	~Stage() = default;

	void update();
	void draw();

	const std::vector<std::vector<Define::BlockCell>> getStage() { return _stage; }
	const int getPointLeftUpX() { return pointLeftUp_x; }
	const int getPointLeftUpY() { return pointLeftUp_y; }
	const char getBlockWidth() { return blockWidth; }
	const char getBlockHeight() { return blockHeight; }
	const char getBlockXNum() { return blockXNum; }
	const char getBlockYNum() { return blockYNum; }

	const Define::BlockCell getBlockCell(int x, int y);

};
