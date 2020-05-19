#pragma once
#include "DxLib.h"
#include "Stage.h"
#include <memory>

using namespace std;

// 敵・プレイヤー・味方かかわらず、画面上のダメージ要素。
// これを生成するオブジェクトは、DamageObjないで定義された動きのみを指定。
class DamageObj
{

	int damagePointLeftUp_x = 0;
	int damagePointLeftUp_y = 0;

	int x = 0;
	int y = 0;
	int damage = 0;

public:
	DamageObj(int _x, int _y, int _damage) {
		x = _x;
		y = _y;
		damage = _damage;
	}
	~DamageObj() = default;

	void update(int shiftXbyPlyr, int shiftingYbyPlyr);
	void draw() {
		DrawCircle(x + damagePointLeftUp_x, y + damagePointLeftUp_y, 3, GetColor(255, 255, 255), true);
	}

};

