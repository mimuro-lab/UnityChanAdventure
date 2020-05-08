
/*!
@file CollisionDetect.h
@brief CollisionDetectクラスが定義されているヘッダファイル
@date 2020/05/04/16:21
@author mimuro
*/

#pragma once

#include <vector>
#include <memory>
#include <DxLib.h>
#include "Define.h"
#include "Stage.h"

/*!
@class CollisionDetect
@brief 当たり判定処理を行うクラス。
@date 2020/05/04/16:21
@author mimuro
*/

using namespace Define;
using namespace std;

class CollisionDetect
{
	//! 当たり判定を格納する変数。Trueだと当たっている。
	struct Collision {
		bool head;
		bool bottom;
		bool right;
		bool left;
	};

	//! 中心座標からどのくらいの範囲で当たり判定を置くか。その範囲の値を管理する構造体。
	struct Collision_range {
		unsigned char head = 0;
		unsigned char bottom = 0;
		unsigned char right = 0;
		unsigned char left = 0;
	};

	//! 当たり判定を管理する変数。
	Collision collisionedSide;

	// プレイヤーオブジェクトの中心点を基準にし、どのくらいの長さで当たり判定を置くか。
	char toRight = 10;
	char toLeft = 10;
	char toHead = 15;
	char toBottom = 30;

	// 各辺に置く当たり判定の点の数。
	char rightPoints = 10;
	char leftPoints = 10;
	char headPoints = 10;
	char bottomPoints = 10;

	//! 現在のプレイヤーの状態を格納する変数。
	Status nowStatus;

	//! ステージの状態を受け取る変数。
	shared_ptr<Stage> _stage;

	//! (x, y)座標は何かに当たっているかどうか
	bool IsDetectedStage(int x, int y);

	//! head部分の衝突の有無を確認する。
	bool detectHead();

	//! right部分の衝突の有無を確認する。
	bool detectRight();

	//! bottom部分の衝突の有無を確認する。
	bool detectBottom();

	//! left部分の衝突の有無を確認する。
	bool detectLeft();

public:
	CollisionDetect(shared_ptr<Stage> __stage, Status _status) {
		// 当たり判定処理は最初無しにする。
		collisionedSide.head = false;
		collisionedSide.bottom = false;
		collisionedSide.right = false;
		collisionedSide.left = false;
		_stage = __stage;
		nowStatus = _status;
	};
	~CollisionDetect() = default;

	//! 当たり判定の範囲を格納する変数。
	Collision_range collisionSideRange;

	//! 更新処理を行う関数。
	void update(Status _nowStatus, shared_ptr<Stage> _stage);

	//! 当たり判定における、方向の定義。
	enum class toShiftDirect{
		right, left, head, bottom, _vertical, _holizen, _none
	};

	//! 水平方向で、任意の距離に障壁があるかどうかを調べる関数。
	bool calcShitingCollisionedSideVertical(toShiftDirect _to, char _range);

	//! 垂直方向で、任意の距離に障壁があるかどうかを調べる関数。
	bool calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range);

	void draw();

	//! 当たり判定を取得する関数。
	Collision getCollisionedSide() { 
		return collisionedSide; 
	}
	//! 中心座標からの当たり判定の範囲を返す関数。
	const char getRange(toShiftDirect _to, int x_vel = 0, int y_vel = 0);

};
