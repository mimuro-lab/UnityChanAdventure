#pragma once

#include "AbsDamageObj.h"
#include "Define.h"
#include <vector>
#include <memory>

using namespace std;
using namespace Define;

class CalcDamagesOverlap
{
	bool calcHeadOverlap(vector<Dimention> characterHeadPoints, vector<shared_ptr<AbsDamageObj>> _damages);
	bool calcBottomOverlap(vector<Dimention> characterBottomPoints, vector<shared_ptr<AbsDamageObj>> _damages);
	bool calcRightOverlap(vector<Dimention> characterRightPoints, vector<shared_ptr<AbsDamageObj>> _damages);
	bool calcLeftOverlap(vector<Dimention> characterLeftPoints, vector<shared_ptr<AbsDamageObj>> _damages);
public:
	CalcDamagesOverlap() {};
	~CalcDamagesOverlap() = default;

	bool isOverlaped(vector<vector<Dimention>> charcterCollisionPoints, vector<shared_ptr<AbsDamageObj>> _damages);

};

