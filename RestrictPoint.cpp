#include "RestrictPoint.h"

Dimention RestrictPoint::update(Dimention nextPoint, Dimention nowVelocity, shared_ptr<CollisionDetect> _collision)
{
	
	Dimention returnPoint = nextPoint;

	// âEÇÃìÆÇ´Çêßå¿Ç∑ÇÈ
	if (nextPoint.x + _collision->getRange(CollisionDetect::toShiftDirect::right)
		> restrictVerticeRight) {
		returnPoint.x = restrictVerticeRight - _collision->getRange(CollisionDetect::toShiftDirect::right);
		isRestrictRight = true;
	}
	else {
		isRestrictRight = false;
	}

	// ç∂ÇÃìÆÇ´Çêßå¿Ç∑ÇÈ
	if (nextPoint.x - _collision->getRange(CollisionDetect::toShiftDirect::left)
		< restrictVerticeLeft) {
		returnPoint.x = restrictVerticeLeft + _collision->getRange(CollisionDetect::toShiftDirect::left);
		isRestrictLeft = true;
	}
	else {
		isRestrictLeft = false;
	}

	// è„ÇÃìÆÇ´Çêßå¿Ç∑ÇÈ
	if (nextPoint.y - _collision->getRange(CollisionDetect::toShiftDirect::head)
		< restrictHorizonHead) {
		returnPoint.y = restrictHorizonHead + _collision->getRange(CollisionDetect::toShiftDirect::head);
		isRestrictHead = true;
	}
	else {
		isRestrictHead = false;
	}

	// â∫ÇÃìÆÇ´Çêßå¿Ç∑ÇÈ
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

int RestrictPoint::getShiftingVelVertical(Dimention nowVelocity, Dimention nowPoint, shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage, PredictPoint predictPoint)
{

	Dimention returnShifting;

	returnShifting.x = returnShifting.y = 0;

	if (isRestrictHorizon())
	{
		// â∫ÇÃèàóù
		if (nowVelocity.y > 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::bottom, std::abs(nowVelocity.y), nowVelocity.x))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage, nowVelocity.x);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = -std::abs(shiftingYRange);
				return returnShifting.y;
			}
		}

		// è„ÇÃèàóù
		if (nowVelocity.y < 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::head, std::abs(nowVelocity.y), nowVelocity.x))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage, nowVelocity.x);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = std::abs(shiftingYRange);
				return returnShifting.y;
			}
		}

		returnShifting.y = -nowVelocity.y;

	}
}

void RestrictPoint::draw()
{
	DrawLine(restrictVerticeRight, 0, restrictVerticeRight, 1000, GetColor(255, 0, 0));
	DrawLine(restrictVerticeLeft, 0, restrictVerticeLeft, 1000, GetColor(255, 0, 0));
	DrawLine(0, restrictHorizonHead, 1000, restrictHorizonHead, GetColor(255, 0, 0));
	DrawLine(0, restrictHorizonBottom, 1000, restrictHorizonBottom, GetColor(255, 0, 0));
}