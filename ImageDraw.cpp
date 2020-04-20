#include "ImageDraw.h"

void ImageDraw::update(int x, int y)
{
	if (NowDraiwngImageIndex >= imageHandles.size()|| NowDraiwngImageIndex > DrawingIndexEnd) {
		IsEnd = true;
		return;
	}

	pointX = x;
	pointY = y;

	NowDrawingImageHandle = imageHandles[NowDraiwngImageIndex];
	
	DrawingSteps_counter++;
	DrawingSteps_counter %= DrawingSteps;
	
	if(DrawingSteps_counter == 0)
		NowDraiwngImageIndex++;
}

void ImageDraw::draw() const
{
	if (IsEnd)
		return;
	DrawRotaGraph(pointX, pointY, 1.0, 0, NowDrawingImageHandle, true);
}