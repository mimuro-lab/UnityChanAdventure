#include "CalcDamagesOverlap.h"

bool CalcDamagesOverlap::calcHeadOverlap(
	vector<Dimention> characterHeadPoints, 
	vector<shared_ptr<AbsDamageObj>> _damages)
{
	bool isOverlaped = false;
	
	int headLeft = characterHeadPoints[0].x;
	int headRight = characterHeadPoints[characterHeadPoints.size() - 1].x;

	DrawLine(headLeft, 0, headLeft, 640, GetColor(0, 255, 0));
	DrawLine(headRight, 0, headRight, 640, GetColor(0, 255, 0));

	//扱うdamageオブジェクトの選別を行う

	vector<shared_ptr<AbsDamageObj>> _calcDamages;

	for (int i = 0; i < _damages.size(); i++) {
		
		int dmgLeft = _damages[i]->getCollisionPoints()[1][0].x;
		int dmgRight =  dmgLeft + abs(_damages[i]->getRange()[2]) + abs(_damages[i]->getRange()[3]);

		if (headRight > dmgLeft || headLeft > dmgRight) {
			_calcDamages.push_back(_damages[i]);
			continue;
		}
	}



	return isOverlaped;
}

bool CalcDamagesOverlap::calcBottomOverlap(
	vector<Dimention> characterBottomPoints,
	vector<shared_ptr<AbsDamageObj>> _damages)
{
	bool isOverlaped = false;
	return isOverlaped;
}

bool CalcDamagesOverlap::calcRightOverlap(
	vector<Dimention> characterRightPoints,
	vector<shared_ptr<AbsDamageObj>> _damages)
{
	bool isOverlaped = false;
	return isOverlaped;
}

bool CalcDamagesOverlap::calcLeftOverlap(
	vector<Dimention> characterLeftPoints,
	vector<shared_ptr<AbsDamageObj>> _damages)
{
	bool isOverlaped = false;
	return isOverlaped;
}

bool CalcDamagesOverlap::isOverlaped(
	vector<vector<Dimention>> charcterCollisionPoints, 
	vector<shared_ptr<AbsDamageObj>> _damages)
{

	bool isOverlapedHead = false;

	isOverlapedHead = calcHeadOverlap(charcterCollisionPoints[0], _damages);

	bool isOverlapedBottom = false;

	isOverlapedBottom = calcBottomOverlap(charcterCollisionPoints[1], _damages);

	bool isOverlapedRight = false;

	isOverlapedRight = calcBottomOverlap(charcterCollisionPoints[2], _damages);

	bool isOverlapedLeft = false;

	isOverlapedLeft = calcBottomOverlap(charcterCollisionPoints[3], _damages);

	return isOverlapedHead || isOverlapedBottom || isOverlapedRight || isOverlapedLeft;
}