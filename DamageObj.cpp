#include "DamageObj.h"

void DamageObj::update(int shiftXbyPlyr, int shiftingYbyPlyr)
{
	damagePointLeftUp_x += shiftXbyPlyr;
	damagePointLeftUp_y += shiftingYbyPlyr;

	nowPoint = pysical.update(nowPoint);

}