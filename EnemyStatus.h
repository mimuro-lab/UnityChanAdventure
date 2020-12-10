#pragma once
#include <DxLib.h>

class EnemyStatus
{
	int pre_hp_kaisou = -1;
public:
	bool isAlive = false;
	bool isActive = false;
	int HitPoint = 0;
	int AllHitPoint = 0;
	int lessHitPoint = 0;

	void acceptDamage(int damage);
	void draw(int leftUp_x, int leftUp_y, int width, int height);
	bool getIsNowDamage();

};

