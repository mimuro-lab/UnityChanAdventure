#pragma once
#include "DxLib.h"
#include "Stage.h"
#include "Define.h"
#include "DamagePysical.h"
#include <memory>

using namespace std;
using namespace Define;

// 敵・プレイヤー・味方かかわらず、画面上のダメージ要素。
// これを生成するオブジェクトは、DamageObjないで定義された動きのみを指定。
class DamageObj
{

	int damagePointLeftUp_x = 0;
	int damagePointLeftUp_y = 0;

	Dimention nowPoint;

	int damage = 0;

	DamagePysical pysical;

public:
	DamageObj(int _x, int _y, int _damage) {
		nowPoint.x = _x;
		nowPoint.y = _y;
		damage = _damage;
	}
	~DamageObj() = default;

	void update(int shiftXbyPlyr, int shiftingYbyPlyr);
	void draw() {
		int drawX = nowPoint.x + damagePointLeftUp_x;
		int drawY = nowPoint.y + damagePointLeftUp_y;
		//DrawFormatString(drawX, drawY, GetColor(255, 255, 255), "x%d, y%d\nlp x%d y%d",x,y, damagePointLeftUp_x ,damagePointLeftUp_y);
		DrawCircle(drawX, drawY, 3, GetColor(255, 255, 255), true);
	}

};

