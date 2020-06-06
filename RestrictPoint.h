#pragma once

#include "Define.h"
#include "DxLib.h"
#include "CollisionDetect.h"
#include "PredictPoint.h"

using namespace Define;
using namespace std;

class RestrictPoint
{

	int restrictVerticeLeft = scrollVerticeLeft;
	int restrictVerticeRight = scrollVerticeRight;

	int restrictHorizonHead = scrollHorizonHead;
	int restrictHorizonBottom = scrollHorizonBottom;
	
	bool isRestrictRight = false;
	bool isRestrictLeft = false;

	bool isRestrictHead = false;
	bool isRestrictBottom = false;

public:
	RestrictPoint() {}
	~RestrictPoint() = default;

	Dimention update(Dimention nextPoint, Dimention nowVelocity, shared_ptr<CollisionDetect> _collision);

	void draw();

	bool isRestrictVertice();
	bool isRestrictHorizon();

	int getShiftingVelVertical(Dimention nowVelocity, 
		Dimention nowPoint, shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage, PredictPoint _predict);

};
