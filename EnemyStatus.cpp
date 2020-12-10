#include "EnemyStatus.h"

void EnemyStatus::acceptDamage(int damage)
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

void EnemyStatus::draw(int leftUp_x, int leftUp_y, int width, int height)
{
	int BoxBotton = leftUp_y + height;

	DrawBox(leftUp_x, leftUp_y, leftUp_x + width, BoxBotton, GetColor(255, 255, 255), false);

	double nowHpPercentage = (double)HitPoint / (double)AllHitPoint;
	int tallOfHp = height * nowHpPercentage;

	// Žc‚èHP‚Ì•`‰æ‚ðs‚¤
	int color = GetColor(0, 255, 0);
	if (HitPoint < lessHitPoint) {
		color = GetColor(255, 0, 0);
	}
	DrawBox(leftUp_x, BoxBotton - tallOfHp, leftUp_x + width, BoxBotton, color, true);
}

bool EnemyStatus::getIsNowDamage()
{
	bool isDamage = false;

	int hp_kaisou = HitPoint / 150;

	if (pre_hp_kaisou != hp_kaisou && pre_hp_kaisou != -1) {
		isDamage = true;
	}
	else {
		isDamage = false;
	}

	pre_hp_kaisou = hp_kaisou;

	return isDamage;

}