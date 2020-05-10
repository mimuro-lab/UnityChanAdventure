#include "RestrictPoint.h"

Dimention RestrictPoint::update(Dimention nextPoint, Dimention nowVelocity, shared_ptr<CollisionDetect> _collision)
{
	
	Dimention returnPoint = nextPoint;

	// ‰E‚Ì“®‚«‚ð§ŒÀ‚·‚é
	if (nextPoint.x + _collision->getRange(CollisionDetect::toShiftDirect::right)
		> restrictVerticeRight) {
		returnPoint.x = restrictVerticeRight - _collision->getRange(CollisionDetect::toShiftDirect::right);
		isRestrictRight = true;
	}
	else {
		isRestrictRight = false;
	}

	// ¶‚Ì“®‚«‚ð§ŒÀ‚·‚é
	if (nextPoint.x - _collision->getRange(CollisionDetect::toShiftDirect::left)
		< restrictVerticeLeft) {
		returnPoint.x = restrictVerticeLeft + _collision->getRange(CollisionDetect::toShiftDirect::left);
		isRestrictLeft = true;
	}
	else {
		isRestrictLeft = false;
	}

	// ã‚Ì“®‚«‚ð§ŒÀ‚·‚é
	if (nextPoint.y - _collision->getRange(CollisionDetect::toShiftDirect::head)
		< restrictHorizonHead) {
		returnPoint.y = restrictHorizonHead + _collision->getRange(CollisionDetect::toShiftDirect::head);
		isRestrictHead = true;
	}
	else {
		isRestrictHead = false;
	}

	// ‰º‚Ì“®‚«‚ð§ŒÀ‚·‚é
	if (nextPoint.y + _collision->getRange(CollisionDetect::toShiftDirect::bottom)
		> restrictHorizonBottom) {
		returnPoint.y = restrictHorizonBottom - _collision->getRange(CollisionDetect::toShiftDirect::bottom);
		isRestrictBottom = true;
	}
	else {
		isRestrictBottom= false;
	}

	return returnPoint;
}

bool RestrictPoint::isRestrictVertice()
{
	return isRestrictRight || isRestrictLeft; 
}

bool RestrictPoint::isRestrictHorizon()
{
	return isRestrictHead || isRestrictBottom;
}

void RestrictPoint::draw()
{
	DrawLine(restrictVerticeRight, 0, restrictVerticeRight, 1000, GetColor(255, 0, 0));
	DrawLine(restrictVerticeLeft, 0, restrictVerticeLeft, 1000, GetColor(255, 0, 0));
	DrawLine(0, restrictHorizonHead, 1000, restrictHorizonHead, GetColor(255, 0, 0));
	DrawLine(0, restrictHorizonBottom, 1000, restrictHorizonBottom, GetColor(255, 0, 0));
}