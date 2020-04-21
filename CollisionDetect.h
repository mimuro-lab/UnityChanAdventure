#pragma once

#include <vector>
#include "Define.h"

class CollisionDetect
{
	struct CollitionPoints {
		std::vector<bool> head;
		std::vector<bool> bottom;
		std::vector<bool> right;
		std::vector<bool> left;
	};

	CollitionPoints _collition;

public:
	CollisionDetect(int headPoints, int bottomPoints, int rightPoints, int leftPoints) {
		_collition.head = std::vector<bool>(headPoints, false);
		_collition.bottom = std::vector<bool>(bottomPoints, false);
		_collition.right = std::vector<bool>(rightPoints, false);
		_collition.left = std::vector<bool>(leftPoints, false);
	};
	~CollisionDetect() = default;

	void update(Define::Status _nowStatus);
	void draw();
};

