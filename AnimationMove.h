#pragma once

#include <memory>
#include <vector>
#include "Define.h"
#include "CollisionDetect.h"
#include "Animation.h"
#include "Pysical.h"
#include "PredictPoint.h"

using namespace Define;

class AnimationMove
{
	Pysical pysical;

	PredictPoint predictPoint;

	// 現在の速度（当たり判定により、これがそのまま有効になるとは限らない）
	Dimention nowVelocity;

	// 実際に有効になる速度
	Dimention validVelocity;

	// 今の座標（更新される前の座標）
	Dimention nowPoint;

	// 次の座標
	Dimention nextPoint;

public:
	AnimationMove(char _walk, char _run, char _jumpUp, char _jumpMidAir){

		nowVelocity.x = nowVelocity.y = 0;

	};

	~AnimationMove() = default;

	Define::Status update(Define::Status nowStatus, Define::rollAction_Basic _isAction, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, std::shared_ptr<Animation> _animation);

};

