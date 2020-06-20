
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
protected:
	//! 当たり判定を格納する変数。Trueだと当たっている。
	struct Collision {
		bool head = false;
		bool bottom = false;
		bool right = false;
		bool left = false;
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

	//! 内側の当たり判定を管理する変数。（プレイヤーがステージにめり込む時に使用する）
	Collision collisionedInSide;

	// プレイヤーオブジェクトの中心点を基準にし、どのくらいの長さで当たり判定を置くか。
	char toRight = 10;
	char toLeft = 10;
	char toHead = 15;
	char toBottom = 30;

	// 各辺に置く当たり判定の点の数。
	char rightPoints;
	char leftPoints;
	char headPoints;
	char bottomPoints;

	//! 現在のプレイヤーの状態を格納する変数。
	Status nowStatus;

	//! ステージの状態を受け取る変数。
	shared_ptr<Stage> _stage;

	//! 角が障壁に当たっているかのフラグ
	bool isCollisionedEdge = false;

	//! (x, y)座標は何かに当たっているかどうか
	bool IsDetectedStage(int x, int y, shared_ptr<Stage> stage);

	//! head部分の衝突の有無を確認する。
	bool detectHead(shared_ptr<Stage> stage, Status nowStatus);

	//! right部分の衝突の有無を確認する。
	bool detectRight(shared_ptr<Stage> stage, Status nowStatus);

	//! bottom部分の衝突の有無を確認する。
	bool detectBottom(shared_ptr<Stage> stage, Status nowStatus);

	//! left部分の衝突の有無を確認する。
	bool detectLeft(shared_ptr<Stage> stage, Status nowStatus);

public:
	CollisionDetect(shared_ptr<Stage> __stage, Status _status,
		char HeadPoints, char BottomPoints, char RightPoints, char LeftPoints,
		char ToHead, char ToBottom, char ToRight, char ToLeft) {
		// 当たり判定処理は最初無しにする。
		collisionedSide.head = false;
		collisionedSide.bottom = false;
		collisionedSide.right = false;
		collisionedSide.left = false;
		_stage = __stage;
		nowStatus = _status;
		
		headPoints = HeadPoints;
		bottomPoints = BottomPoints;
		rightPoints = RightPoints;
		leftPoints = LeftPoints;
		
		toHead = ToHead;
		toBottom = ToBottom;
		toRight = ToRight;
		toLeft = ToLeft;
	};
	~CollisionDetect() = default;

	//! 当たり判定の範囲を格納する変数。
	Collision_range collisionSideRange;

	//! 更新処理を行う関数。
	void update(Status _nowStatus, shared_ptr<Stage> _stage);

	//! 当たり判定における、方向の定義。
	enum class toShiftDirect{
		right, left, head, bottom
	};

	//! 水平方向で、任意の距離に障壁があるかどうかを調べる関数。
	bool calcShitingCollisionedSideVertical(toShiftDirect _to, char _range, char _horizonal_range);

	//! 垂直方向で、任意の距離に障壁があるかどうかを調べる関数。
	bool calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range, char _vertical_range);

	void draw();

	//! 当たり判定を取得する関数。
	Collision getCollisionedSide() { 
		return collisionedSide; 
	}

	//! めり込み当たり判定を取得する関数。
	Collision getCollisionedInSide() {
		return collisionedInSide;
	}

	//! 中心座標からの当たり判定の範囲を返す関数。
	const char getRange(toShiftDirect _to);

	const bool getIsCollisionedEdge() { return isCollisionedEdge; }

	//! 当たり判定すべての座標を取得する
	vector<vector<Dimention>> getCollisionPoints();

};
