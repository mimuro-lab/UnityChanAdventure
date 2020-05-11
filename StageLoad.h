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

	vector<vector<BlockCell>> loadCsv(const char * cavName ,unsigned int loadInitX, unsigned int loadInitY, unsigned char loadWidth, unsigned char loadHeight);

	BlockCell::cellStatus getCellFromInt(int inputInt);

public:
	StageLoad() {
		BlockCell initCell;
		initCell.x1 = initCell.y1 = initCell.x2 = initCell.y2 = 0;
		initCell._status = BlockCell::cellStatus::none;

		_nowStage.assign(blockXNum, vector<BlockCell>(blockYNum, initCell));

	}
	~StageLoad() = default;

	vector<vector<BlockCell>> loadFromFile();

};