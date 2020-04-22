#pragma once

#include <vector>
#include <DxLib.h>

class Stage
{

	struct BlockCell {
		int x1, y1, x2, y2;
	};

	BlockCell initCell;
	
	std::vector<std::vector<BlockCell>> _stage;

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
};
