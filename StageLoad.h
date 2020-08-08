#pragma once

#include "Define.h"
#include "DxLib.h"
#include <vector>

#include <stdio.h>

using namespace std;
using namespace Define;




class StageLoad
{
	vector<vector<BlockCell>> _nowStage;

	vector<vector<BlockCell>> loadCsv(const char * cavName ,int loadInitX, int loadInitY, unsigned char loadWidth, unsigned char loadHeight);

	BlockCell::cellStatus getCellFromInt(int inputInt);

	int nowLoadInitXInd = 0;
	int nowLoadInitYInd = 0;

public:
	StageLoad() {
		BlockCell initCell;
		initCell.x1 = initCell.y1 = initCell.x2 = initCell.y2 = 0;
		initCell._status = BlockCell::cellStatus::none;

		_nowStage.assign(blockXNum, vector<BlockCell>(blockYNum, initCell));

	}
	~StageLoad() = default;

	vector<vector<BlockCell>> loadFromFileInit();

	vector<vector<BlockCell>> loadFromFileForward(unsigned int XInd);

	vector<vector<BlockCell>> loadFromFileBackward(unsigned int XInd);

	vector<vector<BlockCell>> loadFromFileDwonSide(unsigned int YInd);

	vector<vector<BlockCell>> loadFromFileUpSide(unsigned int YInd);

 	const unsigned int getLoadInitAbsX() { return nowLoadInitXInd * blockWidth; }
	const unsigned int getLoadInitAbsY() { return nowLoadInitYInd * blockHeight; }

	const unsigned int getLoadInitIndX() { return nowLoadInitXInd; }
	const unsigned int getLoadInitIndY() { return nowLoadInitYInd; }

};