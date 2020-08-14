#pragma once
#include "Stage.h"
#include "Define.h"
#include <memory>
#include <vector>

class AbsDamageObj
{
protected:
	bool isLive = true;
	bool isDetectEnemy = false;

	// [side][number]
	// sideは0,1,2,3があり、head,bottom,right,left
	// numberは、head,bottomは左から右、right,leftは上から下
	vector<vector<Define::Dimention>> collisionPoints;

public:
	AbsDamageObj() = default;
	~AbsDamageObj() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	virtual void update(std::shared_ptr<Stage> _stage, Dimention shiftingStageVel, Status playerStatus) = 0;

	//! Playerオブジェクトの描画処理全般を行う関数。
	virtual void draw() = 0;

	const bool getIsLive() { return isLive; }

	virtual void adjustBottom(int AdjustRange) = 0;

	virtual vector<vector<Dimention>> getCollisionPoints() = 0;

	virtual vector<int> getRange() = 0;

	virtual void detectEnemy() = 0;

	virtual void detectPlayer() = 0;

	virtual int getDamage() = 0;

};

