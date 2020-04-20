#pragma once
#include <DxLib.h>
#include <vector>
#include <string>

class ImageDraw
{
	std::vector<int> imageHandles;
	char NowDraiwngImageIndex = 0;
	char DrawingIndexEnd = 0;
	int NowDrawingImageHandle = 0;
	char DrawingSteps;
	char DrawingSteps_counter = 0;
	bool IsEnd = false;
	int pointX, pointY;
public:
	ImageDraw(std::vector<int> _imageHandles, int initX, int initY , char _DrawingSteps = 6, char IndexEnd = 99) :
		imageHandles(_imageHandles)
		, NowDrawingImageHandle(_imageHandles[0])
		, pointX(initX)
		, pointY(initY)
		, DrawingIndexEnd(IndexEnd)
		, DrawingSteps(_DrawingSteps)
	{};
	~ImageDraw() = default;

	void update(int x, int y);
	void draw() const;
	const bool isEnd() const { return IsEnd; };

};

