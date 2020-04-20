#pragma once
#include <DxLib.h>
#include "Task.h"
#include "imagePath.h"
#include "ImageDraw.h"
#include <memory>

class Player :
	public Task
{
	std::shared_ptr<ImageDraw> drawingObj = std::make_shared<ImageDraw>(imagePath::getIns()->unityChan_Brake, 100,100);
public:
	Player();
	~Player() = default;

	void update() override;
	void draw() override;
};
