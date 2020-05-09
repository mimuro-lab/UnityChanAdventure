#include "RestrictPoint.h"

Dimention RestrictPoint::update(Dimention nextPoint, shared_ptr<CollisionDetect> _collision)
{
	
	Dimention returnPoint = nextPoint;

	if (nextPoint.x + _collision->getRange(CollisionDetect::toShiftDirect::right) > restrictVerticeRight)
		returnPoint.x = restrictVerticeRight - _collision->getRange(CollisionDetect::toShiftDirect::right);

	if (nextPoint.x - _collision->getRange(CollisionDetect::toShiftDirect::left) < restrictVerticeLeft)
		returnPoint.x = restrictVerticeLeft + _collision->getRange(CollisionDetect::toShiftDirect::left);

	return returnPoint;
}

void RestrictPoint::draw()
{
	DrawLine(restrictVerticeRight, 0, restrictVerticeRight, 1000, GetColor(255, 0, 0));
	DrawLine(restrictVerticeLeft, 0, restrictVerticeLeft, 1000, GetColor(255, 0, 0));
}