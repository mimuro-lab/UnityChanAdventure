#pragma once

#include <vector>
#include <memory>
#include <DxLib.h>
#include "Define.h"
#include "Stage.h"

class CollisionDetect
{
	struct Collision {
		bool head;
		bool bottom;
		bool right;
		bool left;
	};

	Collision collisionedSide;

	// プレイヤーオブジェクトの中心点を基準にする。
	char toRight = 20;
	char toLeft = 20;
	char toHead = 40;
	char toBottom = 40;

	// 当たり判定の点の数
	char rightPoints = 10;
	char leftPoints = 10;
	char headPoints = 10;
	char bottomPoints = 10;

	Define::Status nowStatus;

	std::shared_ptr<Stage> _stage;

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
	CollisionDetect(std::shared_ptr<Stage> __stage, Define::Status _status) {
		collisionedSide.head = false;
		collisionedSide.bottom = false;
		collisionedSide.right = false;
		collisionedSide.left = false;
		_stage = __stage;
		nowStatus = _status;
	};
	~CollisionDetect() = default;

	void update(Define::Status _nowStatus, std::shared_ptr<Stage> _stage);

	enum class toShiftDirect{
		right, left, head, bottom, _vertical, _holizen, _none
	};
	unsigned char _calcRange = 0;
	bool calcShitingCollisionedSideVertical(toShiftDirect _to, unsigned char _range);

	void draw();

	const Collision getCollisionedSide() { return collisionedSide; }

	const char getToBottom() { return toBottom; }
	const char getToHead() { return toHead; }
	const char getRange(toShiftDirect _to, int y_vel = 0, int x_vel = 0);

};
