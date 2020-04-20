#pragma once
#include <DxLib.h>
#include "TreeUtils.h"
#include "Task.h"

class Enemy1
	: public Task
{
public:
	Enemy1();
	~Enemy1() = default;

	void update() override;
	void draw() override;
};

