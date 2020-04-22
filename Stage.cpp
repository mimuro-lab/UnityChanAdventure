#include "Stage.h"

Stage::Stage()
{
	// _stage‚Ì‰Šú‰»
	initCell.x1 = initCell.y1 = initCell.x2 = initCell.y2 = 0;
	_stage.assign(blockXNum, std::vector<BlockCell>(blockYNum, initCell));

	for (char x = 0; x < blockXNum; x++) {
		for (char y = 0; y < blockYNum; y++) {
			_stage[x][y].x1 = pointLeftUp_x + x * blockWidth;
			_stage[x][y].x2 = pointLeftUp_x + x * blockWidth + blockWidth;
			_stage[x][y].y1 = pointLeftUp_y + y * blockHeight;
			_stage[x][y].y2 = _stage[x][y].y1 + blockHeight;
		}
	}
	int x;
}

void Stage::update()
{
}

void Stage::draw()
{
	for (char x = 0; x < blockXNum; x++) {
		for (char y = 0; y < blockYNum; y++) {
			DrawBox(_stage[x][y].x1, _stage[x][y].y1, _stage[x][y].x2, _stage[x][y].y2, GetColor(255, 255, 255), false);
		}
	}
}