#include "Stage.h"

Stage::Stage(unsigned char _blockWidth, unsigned char _blockHeight)
{

	blockWidth = _blockWidth;
	blockHeight = _blockHeight;

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
	for (int x = 0; x < blockXNum; x++) {
		_stage[x][19]._status = _stage[x][0]._status = _stage[x][14]._status
			= Define::BlockCell::cellStatus::block;
	}

	for (int y = 0; y < blockYNum; y++) {
		_stage[0][y]._status = _stage[19][y]._status = Define::BlockCell::cellStatus::block;
	}

	_stage[5][14]._status = _stage[6][14]._status = _stage[7][14]._status = _stage[8][14]._status =
		_stage[1][14]._status = _stage[2][14]._status = _stage[3][14]._status = _stage[4][14]._status
		= Define::BlockCell::cellStatus::none;

	_stage[19][11]._status = _stage[18][11]._status = _stage[17][11]._status = Define::BlockCell::cellStatus::block;
}

void Stage::update()
{
}

void Stage::draw()
{
	for (char x = 0; x < blockXNum; x++) {
		for (char y = 0; y < blockYNum; y++) {
			unsigned int color = GetColor(0, 0, 0);
			if (_stage[x][y]._status == Define::BlockCell::cellStatus::none) {
				//color = GetColor(255, 255, 255);
				continue;
			}
			if (_stage[x][y]._status == Define::BlockCell::cellStatus::block)
				color = GetColor(255, 0, 0);
			DrawBox(_stage[x][y].x1, _stage[x][y].y1, _stage[x][y].x2, _stage[x][y].y2, color, false);
			
		}
	}
}

const Define::BlockCell Stage::getBlockCell(int x, int y)
{
	int _CellXNum = (x - pointLeftUp_x) / blockWidth;
	int _CellYNum = (y - pointLeftUp_x) / blockHeight;

	DrawBox(_stage[_CellXNum][_CellYNum].x1, _stage[_CellXNum][_CellYNum].y1, _stage[_CellXNum][_CellYNum].x2, _stage[_CellXNum][_CellYNum].y2, GetColor(0,0,255), true);

	return _stage[_CellXNum][_CellYNum];

}