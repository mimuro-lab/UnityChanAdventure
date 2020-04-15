#pragma once

#include "Define.h"

class ISceneChanger {
public:
	ISceneChanger() = default;
	~ISceneChanger() = default;
	virtual void changeScene(eScene Next) const = 0;
};