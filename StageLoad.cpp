#include "StageLoad.h"

vector<vector<BlockCell>> StageLoad::loadCsv(const char * csvFile, int loadInitXInd, int loadInitYInd, unsigned char loadWidth, unsigned char loadHeight)
{

	if (loadInitXInd < 0)
		return _nowStage;

	vector<vector<BlockCell>> _stage;

	BlockCell initCell;
	initCell.x1 = initCell.y1 = initCell.x2 = initCell.y2 = 0;
	initCell._status = BlockCell::cellStatus::none;

	_stage.assign(blockXNum, vector<BlockCell>(blockYNum, initCell));

	// 各要素の座標を代入する

	for (int x = 0; x < loadWidth; x++) {
		for (int y = 0; y < loadHeight; y++) {
			_stage[x][y].x1 = loadInitXInd * blockWidth + x * blockWidth;
			_stage[x][y].x2 = _stage[x][y].x1 + blockWidth;
			_stage[x][y].y1 = loadInitYInd * blockHeight + y * blockHeight;
			_stage[x][y].y2 = _stage[x][y].y1 + blockHeight;
		}
	}

	FILE* fp;
	fopen_s(&fp, csvFile, "r");

	if (fp == NULL) {
		
		("ファイルが開けませんでした(in StageLoad::loadCsv)");
		exit(1);
	}

	// CSVファイルを左上から右下まで一行ずつ読み込む。その時の座標を示す。
	unsigned int x = 0;
	unsigned int y = 0;
	// 各要素のインデックスを表す変数。
	unsigned char elementInd = 0;

	// _stageに代入するときに使用するインデックス
	unsigned int _stageXInd = 0;
	unsigned int _stageYInd = 0;

	while (!feof(fp)) {
		int getf = fgetc(fp);

		// 座標の更新
		if (getf == ',') {// ，だったら座標xを一つ増やす
			x++;
			elementInd = 0;
		}
		else if (getf == '\n') {// 改行だったら座標yを一つ増やす
			x = 0;
			y++;
			elementInd = 0;
			if(y > loadInitYInd)
				_stageYInd++;
			_stageXInd = 0;
		}
		else {// ，でも改行でもない時、要素を読み込んだという事なので、
			elementInd++;
			int correctInt = getf - 48;

			// xとyが読み込み範囲ないにあれば_stageに代入する。
			if (x >= loadInitXInd && x < (loadInitXInd + loadWidth)) {
				
				if (y >= loadInitYInd && y < (loadInitYInd + loadHeight)) {

					if(_stageXInd < blockXNum && _stageYInd < blockYNum)
						_stage[_stageXInd][_stageYInd]._status = getCellFromInt(correctInt);

					_stageXInd++;

				}
			}
		}
	}

	return _stage;

	fclose(fp);
}

BlockCell::cellStatus StageLoad::getCellFromInt(int inputInt)
{
	switch (inputInt) {
	case 1:
		return BlockCell::cellStatus::block;
		break;
	}

	//　どれにも当てはまらなかったらブロック無し
	return BlockCell::cellStatus::none;
}

vector<vector<BlockCell>> StageLoad::loadFromFileInit()
{
	vector<vector<BlockCell>> _stage = _nowStage;

	nowLoadInitXInd = 0;
	nowLoadInitYInd = 0;
	
	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;

}

vector<vector<BlockCell>> StageLoad::loadFromFileForward(unsigned int XInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	nowLoadInitXInd += XInd;
	
	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

 	_nowStage = _stage;

	return _stage;

}

vector<vector<BlockCell>> StageLoad::loadFromFileBackward(unsigned int XInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	// 左向きの時点で、nowとnextよりblockXNum分小さい。
	nowLoadInitXInd -= XInd;
	
	if (nowLoadInitXInd < 0)
		nowLoadInitXInd = 0;

	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;

}

vector<vector<BlockCell>> StageLoad::loadFromFileDwonSide(unsigned int YInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	nowLoadInitYInd += YInd;

	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;
}

vector<vector<BlockCell>> StageLoad::loadFromFileUpSide(unsigned int YInd)
{
	vector<vector<BlockCell>> _stage = _nowStage;

	// 左向きの時点で、nowとnextよりblockXNum分小さい。
	nowLoadInitYInd -= YInd;

	if (nowLoadInitYInd < 0)
		nowLoadInitYInd = 0;

	_stage = loadCsv("./Stage/sample_stage.csv", nowLoadInitXInd, nowLoadInitYInd, blockXNum, blockYNum);

	_nowStage = _stage;

	return _stage;

}