#pragma once

#include "Define.h"
#include "DxLib.h"
#include "CollisionDetect.h"

using namespace Define;
using namespace std;

class RestrictPoint
{

	int restrictVerticeLeft = 50;
	int restrictVerticeRight = 500;

public:
	RestrictPoint() {}
	~RestrictPoint() = default;

	Dimention update(Dimention nextPoint, shared_ptr<CollisionDetect> _collision);

	void draw();
};
