#pragma once

#include "AbsDamageObj.h"
#include "Define.h"
#include <vector>
#include <memory>

using namespace std;
using namespace Define;

class CalcDamagesOverlap
{
	bool calcVerticalOverlap(vector<Dimention> characterHeadPoints, vector<Dimention> characterBottomPoints, vector<shared_ptr<AbsDamageObj>> _damages);

	bool calcHorizonalOverlap(vector<Dimention> characterRightPoints, vector<Dimention> characterLeftPoints, vector<shared_ptr<AbsDamageObj>> _damages);

public:
	CalcDamagesOverlap() {};
	~CalcDamagesOverlap() = default;

	bool isOverlaped(vector<vector<Dimention>> charcterCollisionPoints, vector<shared_ptr<AbsDamageObj>> _damages);

};

