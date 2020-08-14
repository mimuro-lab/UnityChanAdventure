#include "CalcDamagesOverlap.h"

bool CalcDamagesOverlap::calcVerticalOverlap(
	vector<Dimention> characterHeadPoints, 
	vector<Dimention> characterBottomPoints,
	vector<shared_ptr<AbsDamageObj>> _damages)
{
	detectedDamageIndex.clear();

	bool isOverlaped = false;
	
	int headLeft = characterHeadPoints[0].x;
	int headRight = characterHeadPoints[characterHeadPoints.size() - 1].x;

	//DrawLine(headLeft, 0, headLeft, 640, GetColor(0, 255, 255));
	//DrawLine(headRight, 0, headRight, 640, GetColor(0, 255, 255));

	//扱うdamageオブジェクトの選別を行う

	vector<shared_ptr<AbsDamageObj>> _calcDamages;

	for (int i = 0; i < _damages.size(); i++) {

		int dmgLeft = _damages[i]->getCollisionPoints()[1][0].x;
		int dmgRight = dmgLeft + abs(_damages[i]->getRange()[2]) + abs(_damages[i]->getRange()[3]);

		if (headRight > dmgLeft && headLeft < dmgRight) {
			_calcDamages.push_back(_damages[i]);
			continue;
		}
	}

	// damageオブジェクトの選別後、各点の判定を行う

	// headより上にあるdamageオブジェクトは入れない変数

	for (int i = 0; i < _calcDamages.size(); i++) {

		// 垂直方向で、かぶっているかどうかを判断する。
		for (int j = 0; j < _calcDamages[i]->getCollisionPoints().size(); j++) {

			bool isOverlapedHead = false;
			int dmgXBottom = _calcDamages[i]->getCollisionPoints()[1][j].x;
			int dmgYBottom = _calcDamages[i]->getCollisionPoints()[1][j].y;

			// headの各座標と比べる
			for (int headNum = 0; headNum < characterHeadPoints.size(); headNum++) {
				int headX = characterHeadPoints[headNum].x;
				int headY = characterHeadPoints[headNum].y;
				if (dmgYBottom > headY) {// headより下にある
					//DrawLine(headX, headY, dmgXBottom, dmgYBottom, GetColor(255, 0, 0));
					isOverlapedHead = true;
					//break;
				}
				else {
					//DrawLine(headX, headY, dmgX, dmgY, GetColor(255, 255, 255));
				}
			}

			bool isOverlapedBottom = false;
			int dmgXHead = _calcDamages[i]->getCollisionPoints()[0][j].x;
			int dmgYHead = _calcDamages[i]->getCollisionPoints()[0][j].y;

			for (int bottomNum = 0; bottomNum < characterBottomPoints.size(); bottomNum++) {
				int bottomX = characterBottomPoints[bottomNum].x;
				int bottomY = characterBottomPoints[bottomNum].y;
				if (dmgYHead < bottomY) {// bottomより下にある
					//DrawLine(bottomX, bottomY, dmgXHead, dmgYHead, GetColor(255, 255, 0));
					isOverlapedBottom = true;
					//break;
				}
				else {
					//DrawLine(bottomX, bottomY, dmgX, dmgY, GetColor(255, 255, 255));
				}
			}

			isOverlaped = isOverlapedHead && isOverlapedBottom;

			if (isOverlaped) {
				detectedDamageIndex.push_back(i);
				break;
			}
		}
	}

	return isOverlaped;
}

bool CalcDamagesOverlap::calcHorizonalOverlap(
	vector<Dimention> characterRightPoints,
	vector<Dimention> characterLeftPoints,
	vector<shared_ptr<AbsDamageObj>> _damages)
{
	detectedDamageIndex.clear();

	bool isOverlaped = false;
	int rightHead = characterRightPoints[0].y;
	int rightBottom = characterRightPoints[characterRightPoints.size() - 1].y;

	//DrawLine(0, rightHead, 640, rightHead, GetColor(0, 255, 0));
	//DrawLine(0, rightBottom, 640, rightBottom, GetColor(0, 255, 0));

	//扱うdamageオブジェクトの選別を行う

	vector<shared_ptr<AbsDamageObj>> _calcDamages;

	for (int i = 0; i < _damages.size(); i++) {

		int dmgHead = _damages[i]->getCollisionPoints()[3][0].y;
		int dmgBottom = dmgHead + abs(_damages[i]->getRange()[0]) + abs(_damages[i]->getRange()[1]);

		//DrawLine(0, dmgHead, 640, dmgHead, GetColor(255, 255, 255));
		//DrawLine(0, dmgBottom, 640, dmgBottom, GetColor(255, 255, 255));

		if (rightHead < dmgBottom && rightBottom > dmgHead){
			_calcDamages.push_back(_damages[i]);
			continue;
		}
	}

	//printfDx("%d %d\n", _damages.size(), _calcDamages.size());
	
	// damageオブジェクトの選別後、各点の判定を行う

	// Rightより上にあるdamageオブジェクトは入れない変数

	for (int i = 0; i < _calcDamages.size(); i++) {

		// 水平方向で、かぶっているかどうかを判断する。
		for (int j = 0; j < _calcDamages[i]->getCollisionPoints().size(); j++) {
			// DamageのLeftの各点の座標
			bool isOverlapedLeft = false;
			int dmgXLeft = _calcDamages[i]->getCollisionPoints()[3][j].x;
			int dmgYLeft = _calcDamages[i]->getCollisionPoints()[3][j].y;

			// キャラのRightの各座標と比べる
			for (int RightNum = 0; RightNum < characterRightPoints.size(); RightNum++) {
				int RightX = characterRightPoints[RightNum].x;
				int RightY = characterRightPoints[RightNum].y;
				//DrawCircle(RightX, RightY, 2, GetColor(255, 0, 0));
				//DrawLine(RightX, RightY, dmgX, dmgY, GetColor(255, 0, 0));
				if (dmgXLeft < RightX) {// Rightより下にある
					//DrawLine(RightX, RightY, dmgXLeft, dmgYLeft, GetColor(0, 0, 255));
					isOverlapedLeft = true;
				}
				else {
					//DrawLine(RightX, RightY, dmgX, dmgY, GetColor(255, 255, 255));
				}
			}

			// DamageのRightの各点の座標
			bool isOverlapedRight = false;
			int dmgXRight = _calcDamages[i]->getCollisionPoints()[2][j].x;
			int dmgYRight = _calcDamages[i]->getCollisionPoints()[2][j].y;
			// キャラのLeftの各座標と比べる
			for (int LeftNum = 0; LeftNum < characterLeftPoints.size(); LeftNum++) {
				int LeftX = characterLeftPoints[LeftNum].x;
				int LeftY = characterLeftPoints[LeftNum].y;
				//DrawCircle(LeftX, LeftY, 2, GetColor(255, 0, 0));
				//DrawLine(LeftX, LeftY, dmgX, dmgY, GetColor(255, 0, 0));
				if (dmgXRight > LeftX) {// Leftより下にある
					//DrawLine(LeftX, LeftY, dmgXRight, dmgYRight, GetColor(255, 0, 0));
					isOverlapedRight = true;
				}
				else {
					//DrawLine(LeftX, LeftY, dmgX, dmgY, GetColor(255, 255, 255));
				}
			}

			isOverlaped = isOverlapedLeft && isOverlapedRight;

			if (isOverlaped) {
				detectedDamageIndex.push_back(i);
				break;
			}
		}
	}

	return isOverlaped;
}

bool CalcDamagesOverlap::isOverlaped(
	vector<vector<Dimention>> charcterCollisionPoints, 
	vector<shared_ptr<AbsDamageObj>> _damages,
	bool isCharacterAlive
)
{
	// 敵が死んでいる状態だったら、ダメージオブジェクトが敵に当たる事はあり得ない。
	// よって、常にFalseを返す。
	if (!isCharacterAlive) {
		// 消去対象のダメージオブジェクトはない。
		detectedDamageIndex.clear();
		return false;
	}

	bool isOverlapedVertical = false;

	isOverlapedVertical = calcVerticalOverlap(charcterCollisionPoints[0], charcterCollisionPoints[1], _damages);


	bool isOverlapedHorizonal = false;

	isOverlapedHorizonal = calcHorizonalOverlap(charcterCollisionPoints[2], charcterCollisionPoints[3], _damages);

	return isOverlapedVertical || isOverlapedHorizonal;
}

void CalcDamagesOverlap::refreshDetectedDamageIndex()
{
	std::sort(detectedDamageIndex.begin(), detectedDamageIndex.end());
	detectedDamageIndex.erase(std::unique(detectedDamageIndex.begin(), detectedDamageIndex.end()), detectedDamageIndex.end());

}

void CalcDamagesOverlap::update()
{

}