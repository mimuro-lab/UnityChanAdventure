#include "AnimationMovePlayer.h"

Status AnimationMovePlayer::update(
	Status nowStatus,
	characterAction nowAction,
	shared_ptr<CollisionDetect> _collision,
	shared_ptr<Stage> _stage,
	shared_ptr<Animation> _animation, 
	VirtualController controller
)
{
	Status _nextStatus = nowStatus;

	// クラス内変数のnowPointを更新
	nowPoint.x = nowStatus._x;
	nowPoint.y = nowStatus._y;

	// Pysicalクラスにより、現在の状態から現在の速度を計算する。
	nowVelocity = pysical.update(nowAction, nowStatus.directRight, controller, _collision);
	nowVelocity = pysical.resetVelocity(nowVelocity, _collision);

	// PredictPointクラスにより、その速度の座標位置が妥当であるか判断し、妥当な座標位置を計算する。
	nextPoint = predictPoint.update(nowPoint, nowVelocity, _collision, _stage);

	// RestrictPointクラスにより、画面上で動きを制限する。
	nextPoint = restrictPoint.update(nextPoint, nowVelocity, _collision);

	//restrictPoint.draw();

	// nextPointをStatus型変数の座標位置に代入し、返す。
	_nextStatus._x = nextPoint.x;
	_nextStatus._y = nextPoint.y;

	// 速度も代入する
	_nextStatus._x_speed = nowVelocity.x;
	_nextStatus._y_speed = nowVelocity.y;

	//DrawFormatString(100, 50, GetColor(255, 255, 255), "next point x:%d, y:%d", nextPoint.x, nextPoint.y);

	return _nextStatus;
}


Dimention AnimationMovePlayer::getShiftingStage(shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage)
{

	Dimention returnShifting;
	
	returnShifting.x = returnShifting.y = 0;

	if (restrictPoint.isRestrictHorizon())
	{
		// 下の処理
		if (nowVelocity.y > 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::bottom, std::abs(nowVelocity.y), nowVelocity.x))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage, nowVelocity.x);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = -std::abs(shiftingYRange);
				return returnShifting;
			}
		}

		// 上の処理
		if (nowVelocity.y < 0) {
			if (_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::head, std::abs(nowVelocity.y), nowVelocity.x))
			{
				int fittingY = predictPoint.fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage, nowVelocity.x);
				int shiftingYRange = fittingY - nowPoint.y;
				returnShifting.y = std::abs(shiftingYRange);
				return returnShifting;
			}
		}

		returnShifting.y = -nowVelocity.y;

	}

	if (restrictPoint.isRestrictVertice())
	{
		// 右の処理
		if (nowVelocity.x > 0) {
			if (_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::right, std::abs(nowVelocity.x), nowVelocity.y))
			{
				int fittingX = predictPoint.fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage, nowVelocity.y);
				int shiftingXRange = fittingX - nowPoint.x;
				returnShifting.x = -std::abs(shiftingXRange);
				return returnShifting;
			}
		}

		//　左の処理
		if (nowVelocity.x < 0) {
			if (_collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::left, std::abs(nowVelocity.x), nowVelocity.y))
			{
				int fittingX = predictPoint.fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage, nowVelocity.y);
				int shiftingXRange = fittingX - nowPoint.x;
				returnShifting.x = std::abs(shiftingXRange);
				return returnShifting;
			}
		}

		returnShifting.x = -nowVelocity.x;

	}

	
	return returnShifting;

}