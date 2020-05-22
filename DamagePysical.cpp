#include "DamagePysical.h"

Dimention DamagePysical::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc)
{
	Dimention nextVel = affectedVel;

	nextVel.x += affectAcc.x;
	nextVel.y += affectAcc.y;

	return nextVel;
}

Dimention DamagePysical::calcPointFromVelocity(Dimention affectPoint, Dimention affectVel)
{
	Dimention nextPoint = affectPoint;

	nextPoint.x += affectVel.x;
	nextPoint.y += affectVel.y;

	return nextPoint;
}

Dimention DamagePysical::update(Dimention nowPoint)
{
	Dimention nextPoint = nowPoint;

	accel = affectGravity(accel);

	velocity = calcVelocityFromAccel(velocity, accel);

	nextPoint = calcPointFromVelocity(nextPoint, velocity);

	return nextPoint;
}
