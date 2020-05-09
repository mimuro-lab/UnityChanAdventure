#include "RestrictPoint.h"

Dimention RestrictPoint::update(Dimention nextPoint, Dimention nowVelocity, shared_ptr<CollisionDetect> _collision)
{
	
	Dimention returnPoint = nextPoint;

	if (nextPoint.x + _collision->getRange(CollisionDetect::toShiftDirect::right)
		> restrictVerticeRight) {
		returnPoint.x = restrictVerticeRight - _collision->getRange(CollisionDetect::toShiftDirect::right);
		//if (!_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::right, std::abs(nowVelocity.x)))
			isRestricRight = true;
		//else
			//isRestricRight = false;
	}
	else {
		isRestricRight = false;
	}

	if (nextPoint.x - _collision->getRange(CollisionDetect::toShiftDirect::left)
		< restrictVerticeLeft) {
		returnPoint.x = restrictVerticeLeft + _collision->getRange(CollisionDetect::toShiftDirect::left);
		//if (!_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::left, std::abs(nowVelocity.x)))
			isRestricLeft = true;
		//else
			//isRestricLeft = false;
	}
	else {
		isRestricLeft = false;
	}
	return returnPoint;
}

bool RestrictPoint::isRestricVertice()
{
	return isRestricRight || isRestricLeft; 
}

void RestrictPoint::draw()
{
	DrawLine(restrictVerticeRight, 0, restrictVerticeRight, 1000, GetColor(255, 0, 0));
	DrawLine(restrictVerticeLeft, 0, restrictVerticeLeft, 1000, GetColor(255, 0, 0));
}