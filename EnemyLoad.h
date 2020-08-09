#pragma once
//#include "Enemy.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <DxLib.h>

using namespace std;

enum class EnemyType {
	Enemy1,
	Enemy2,
	_end,
};

struct EnemyElement {
	EnemyType type = EnemyType::_end;
	int x = 0;
	int y = 0;
	int hitPoint = 0;
	bool isAlive = false;
};

class EnemyLoad
{
	vector<EnemyElement> elements;

	EnemyType getType(int _readValue);
	bool getAlive(int _readValue);

public:
	EnemyLoad();
	~EnemyLoad() = default;

	const vector<EnemyElement> getElements() { return elements; }

};


