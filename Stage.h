#pragma once

#include <vector>
#include <DxLib.h>
#include "Define.h"
#include "StageLoad.h"

using namespace std;
using namespace Define;

class Stage
{
private:
	BlockCell initCell;
	
	vector<vector<BlockCell>> _stage;

	int pointLeftUp_x = 0;
	int pointLeftUp_y = 0;

	StageLoad _load;

	int nowAbsoluteX = 0;
	int nowAbsoluteY = 0;

	// ï\é¶ÇµÇƒÇ¢ÇÈ_stageè„ÇÃç¿ïW
	int nowPointOnDrawingX = 0;
	int nowPointOnDrawingY = 0;

public:
	
	unsigned char blockWidth;
	unsigned char blockHeight;

	Stage(unsigned char blockWidth, unsigned char blockHeight);
	~Stage() = default;

	void update(Dimention shifting, Status nowStatus);
	void draw();

	const vector<vector<BlockCell>> getStage() { return _stage; }
	const int getPointLeftUpX() { return pointLeftUp_x; }
	const int getPointLeftUpY() { return pointLeftUp_y; }
	const char getBlockWidth() { return blockWidth; }
	const char getBlockHeight() { return blockHeight; }
	const char getBlockXNum() { return blockXNum; }
	const char getBlockYNum() { return blockYNum; }

	const BlockCell getBlockCell(int x, int y);

	const unsigned int getAbsIndInitDrawingLeftUpX() { return _load.getLoadInitIndX(); }
	const unsigned int getAbsIndInitDrawingLeftUpY() { return _load.getLoadInitIndY(); }

	void adjustBottom(int AdjustRange);

};
