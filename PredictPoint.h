#pragma once

#include "Define.h"
#include "Pysical.h"
#include "CollisionDetect.h"

using namespace Define;

class PredictPoint
{

	// 更新前の位置
	Dimention nowPoint;

	// 次のコマで位置するであろう座標
	Dimention predictPoint;

	Dimention calcPredictPoint(Dimention nowPoint, Dimention nowVelocity);

	int fittingPointHorizon(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

	int fittingPointVertical(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

	int getForwardBlockNearSideVertical(
		Dimention nowPoint,
		int predictRange,
		std::shared_ptr<CollisionDetect> _collision,
		std::shared_ptr<Stage> _stage
	);

	int getForwardBlockNearSideHorizon(
		Dimention nowPoint,
		int predictRange,
		std::shared_ptr<CollisionDetect> _collision,
		std::shared_ptr<Stage> _stage
	);

public:
	PredictPoint() {
		predictPoint.x = predictPoint.y = 0;
		nowPoint.x = nowPoint.y =  0;
	}
	~PredictPoint() = default;

	Dimention update(Dimention nowPoint, Dimention nowVelocity, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

};