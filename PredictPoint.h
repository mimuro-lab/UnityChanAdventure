
/*!
@file PredictPoint.h
@brief PredictPointクラスが定義されているヘッダファイル。
@date 2020/05/04/17:56
@author mimuro
*/

#pragma once

#include "Define.h"
#include "Pysical.h"
#include "CollisionDetect.h"

/*!
@class PredictPoint
@brief 座標が適切かどうかを判断するためのクラス。
@date 2020/05/04/17:59
@author mimuro
*/
using namespace Define;

class PredictPoint
{

	//! 更新前の位置
	Dimention nowPoint;

	//! 次のコマで位置するであろう座標
	Dimention predictPoint;

	//! 今の座標から、今の速度により次の座標を計算する。
	Dimention calcPredictPoint(Dimention nowPoint, Dimention nowVelocity);

	//! 水平方向の一番近いブロックの一番近い辺のX座標を取得する。
	int getForwardBlockNearSideHorizon(
		Dimention nowPoint,
		int predictRange,
		std::shared_ptr<CollisionDetect> _collision,
		std::shared_ptr<Stage> _stage
	);

	//! 垂直方向の一番近いブロックの一番近い辺のX座標を取得する。
	int getForwardBlockNearSideVertical(
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

	//! 更新処理を行う関数。
	Dimention update(Dimention nowPoint, Dimention nowVelocity, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

	//! 水平方向に動く場合の適切な座標の修正を行う関数。
	int fittingPointHorizon(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, char _verticalRange);

	//! 垂直方向に動く場合の適切な座標の修正を行う関数。
	int fittingPointVertical(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, char _horizonalRange);

};