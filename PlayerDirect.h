#pragma once

#include "Define.h"
#include "Controller.h"

class PlayerDirect
{
public:
	PlayerDirect() = default;
	~PlayerDirect() = default;

	bool updateDirect(Define::rollAction_Basic nowAction, bool nowDirectRight);
};