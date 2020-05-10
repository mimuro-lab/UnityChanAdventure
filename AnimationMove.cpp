
/*!
@file AnimationMove.cpp
@brief AnimationMoveクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/05/04/14:38
@author mimuro
*/

#include "AnimationMove.h"

/*!
@brief Status型の現在現在の状態を入力し、次のコマの座標位置を更新しを返す。
@date 2020/05/04/14:38
@author mimuro
*/
Status AnimationMove::update(
	Status nowStatus, 
	rollAction_Basic nowAction, 
	shared_ptr<CollisionDetect> _collision, 
	shared_ptr<Stage> _stage, 
	shared_ptr<Animation> _animation
)
{
	Status _nextStatus = nowStatus;

	// クラス内変数のnowPointを更新
	nowPoint.x = nowStatus._x;
	nowPoint.y = nowStatus._y;

	// Pysicalクラスにより、現在の状態から現在の速度を計算する。
	nowVelocity = pysical.update(nowAction, nowStatus.directRight);
	nowVelocity = pysical.resetVelocity(nowVelocity, _collision);

	// PredictPointクラスにより、その速度の座標位置が妥当であるか判断し、妥当な座標位置を計算する。
	nextPoint = predictPoint.update(nowPoint ,nowVelocity, _collision, _stage);

	// RestrictPointクラスにより、画面上で動きを制限する。
	nextPoint = restrictPoint.update(nextPoint, nowVelocity, _collision);

	restrictPoint.draw();

	// nextPointをStatus型変数の座標位置に代入し、返す。
	_nextStatus._x = nextPoint.x;
	_nextStatus._y = nextPoint.y;

	// 速度も代入する
	_nextStatus._x_speed = nowVelocity.x;
	_nextStatus._y_speed = nowVelocity.y;

	return _nextStatus;
	
}

Dimention AnimationMove::getShiftingStage(shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage)
{

	Dimention returnShifting;

	returnShifting.x = returnShifting.y = 0;

	if (restrictPoint.isRestrictVertice())
	{
		if (nowVelocity.x > 0) {
			if (_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::right, std::abs(nowVelocity.x))) 
			{
				int fittingX = predictPoint.fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage);
				int shiftingXRange = fittingX - nowPoint.x;
				returnShifting.x = -std::abs(shiftingXRange);
				return returnShifting;
			}
		}

		if (nowVelocity.x < 0) {
			if (_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::left, std::abs(nowVelocity.x))) 
			{
				int fittingX = predictPoint.fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage);
				int shiftingXRange = fittingX - nowPoint.x;
				returnShifting.x = std::abs(shiftingXRange);
				return returnShifting;
			}
		}

		returnShifting.x = -nowVelocity.x;

	}

	if (restrictPoint.isRestrictHorizon())
	{
		// 下の処理
		if (nowVelocity.y > 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::bottom, std::abs(nowVelocity.y)))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = -std::abs(shiftingYRange);
				return returnShifting;
			}
		}

		// 上の処理
		if (nowVelocity.y < 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::head, std::abs(nowVelocity.y)))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = std::abs(shiftingYRange);
				return returnShifting;
			}
		}

		returnShifting.y = -nowVelocity.y;

	}

	return returnShifting;

}