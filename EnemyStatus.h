#pragma once
class EnemyStatus
{
public:
	bool isAlive = false;
	bool isActive = false;
	int HitPoint = 0;

	void acceptDamage(int damage);

};

