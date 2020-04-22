#include "Stage.h"

Stage::Stage()
{
	// _stage‚Ì‰Šú‰»
	initCell.x1 = initCell.y1 = initCell.x2 = initCell.y2 = 0;
	initCell._status = Define::BlockCell::cellStatus::none;
	_stage.assign(blockXNum, std::vector<Define::BlockCell>(blockYNum, initCell));

	for (char x = 0; x < blockXNum; x++) {
		for (char y = 0; y < blockYNum; y++) {
			_stage[x][y].x1 = pointLeftUp_x + x * blockWidth;
			_stage[x][y].x2 = pointLeftUp_x + x * blockWidth + blockWidth;
			_stage[x][y].y1 = pointLeftUp_y + y * blockHeight;
			_stage[x][y].y2 = _stage[x][y].y1 + blockHeight;
		}
	}
	_stage[5][5]._status = Define::BlockCell::cellStatus::block;
}

void Stage::update()
{
}

void Stage::draw()
{
	for (char x = 0; x < blockXNum; x++) {
		for (char y = 0; y < blockYNum; y++) {
			unsigned int color = GetColor(0, 0, 0);
			if (_stage[x][y]._status == Define::BlockCell::cellStatus::none)
				color = GetColor(0, 0, 0);
			if (_stage[x][y]._status == Define::BlockCell::cellStatus::block) {
				color = GetColor(255, 0, 0);
				DrawBox(_stage[x][y].x1, _stage[x][y].y1, _stage[x][y].x2, _stage[x][y].y2, color, true);
			}
			
		}
	}
}