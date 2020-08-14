#pragma once
class PlayerStatus
{
public:
	bool isAlive = false;
	bool isActive = false;
	int HitPoint = 0;

	void acceptDamage(int damage);
};

