#pragma once

#include "Define.h"
#include "DxLib.h"
#include "CollisionDetect.h"

using namespace Define;
using namespace std;

class RestrictPoint
{

	int restrictVerticeLeft = 150;
	int restrictVerticeRight = 500;

	int restrictHorizonHead = 150;
	int restrictHorizonBottom = 500;
	
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
