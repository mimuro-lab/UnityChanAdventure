#include "PlayerStatus.h"

void PlayerStatus::acceptDamage(int damage)
{
	if (HitPoint > 0) {
		HitPoint -= damage;
		if (HitPoint < 0)
			HitPoint = 0;
	}
	else {
		isAlive = false;
	}
}