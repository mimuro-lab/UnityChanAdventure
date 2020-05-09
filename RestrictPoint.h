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
	
	bool isRestricRight = false;
	bool isRestricLeft = false;

public:
	RestrictPoint() {}
	~RestrictPoint() = default;

	Dimention update(Dimention nextPoint, Dimention nowVelocity, shared_ptr<CollisionDetect> _collision);

	void draw();

	bool isRestricVertice();

};
