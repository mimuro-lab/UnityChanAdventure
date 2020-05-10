#pragma once

#include "Define.h"
#include "DxLib.h"
#include "CollisionDetect.h"

using namespace Define;
using namespace std;

class RestrictPoint
{

	int restrictVerticeLeft = 200;
	int restrictVerticeRight = 400;

	int restrictHorizonHead = 300;
	int restrictHorizonBottom = 400;
	
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

};
