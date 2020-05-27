#pragma once
#include "Stage.h"
#include "Define.h"
#include <memory>

class AbsDamageObj
{
protected:
	bool isLive = true;
public:
	AbsDamageObj() = default;
	~AbsDamageObj() = default;

	//! Playerオブジェクトの前処理全般を行う関数。
	virtual void update(std::shared_ptr<Stage> _stage, Dimention shiftingStageVel, Status playerStatus) = 0;

	//! Playerオブジェクトの描画処理全般を行う関数。
	virtual void draw() = 0;

	const bool getIsLive() { return isLive; }
};

