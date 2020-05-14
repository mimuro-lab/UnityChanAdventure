#include "Stage.h"

Stage::Stage(unsigned char _blockWidth, unsigned char _blockHeight)
{

	blockWidth = _blockWidth;
	blockHeight = _blockHeight;

	// _stageÇÃèâä˙âª
	initCell.x1 = initCell.y1 = initCell.x2 = initCell.y2 = 0;
	initCell._status = BlockCell::cellStatus::none;

	_stage.assign(blockXNum, vector<BlockCell>(blockYNum, initCell));

	_stage = _load.loadFromFileInit();

}

void Stage::update(Dimention shifting, Status nowStatus)
{
	pointLeftUp_x += shifting.x;
	pointLeftUp_y += shifting.y;

	nowAbsoluteX = nowStatus._x - pointLeftUp_x;
	nowAbsoluteY = nowStatus._y - pointLeftUp_y;

	nowPointOnDrawingX = nowAbsoluteX - _load.getLoadInitAbsX();
	nowPointOnDrawingY = nowAbsoluteY - _load.getLoadInitAbsY();

	if (nowPointOnDrawingX > blockWidth * 30) {
  		_stage = _load.loadFromFileForward(10);
	}

	if (nowPointOnDrawingX < blockWidth * 10 && nowAbsoluteX > blockWidth * 10) {
		_stage = _load.loadFromFileBackward(10);
	}

	if (nowPointOnDrawingY > blockHeight * 30) {
		_stage = _load.loadFromFileDwonSide(10);
	}

	if (nowPointOnDrawingY < blockHeight * 10 && nowAbsoluteY > blockHeight * 10) {
		_stage = _load.loadFromFileUpSide(10);
	}

}

void Stage::draw()
{
	for (char x = 0; x < blockXNum; x++) {
		for (char y = 0; y < blockYNum; y++) {
			unsigned int color = GetColor(0, 0, 0);
			if (_stage[x][y]._status == BlockCell::cellStatus::none) {
				//color = GetColor(255, 255, 255);
				continue;
			}
			if (_stage[x][y]._status == BlockCell::cellStatus::block)
				color = GetColor(255, 0, 0);
			DrawBox(_stage[x][y].x1 + pointLeftUp_x, _stage[x][y].y1 + pointLeftUp_y,
				_stage[x][y].x2 + pointLeftUp_x, _stage[x][y].y2 + pointLeftUp_y, color, false);
			
		}
	}

}

const BlockCell Stage::getBlockCell(int x, int y)
{
	int _CellXNum = (x - pointLeftUp_x) / blockWidth - _load.getLoadInitIndX();
	int _CellYNum = (y - pointLeftUp_y) / blockHeight - _load.getLoadInitIndY();

	DrawBox(_stage[_CellXNum][_CellYNum].x1 + pointLeftUp_x, _stage[_CellXNum][_CellYNum].y1 + pointLeftUp_y
		, _stage[_CellXNum][_CellYNum].x2 + pointLeftUp_x, _stage[_CellXNum][_CellYNum].y2 + pointLeftUp_y, GetColor(0, 0, 255), true);

	return _stage[_CellXNum][_CellYNum];

}