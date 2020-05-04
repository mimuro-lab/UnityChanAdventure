
/*!
@file PredictPoint.cpp
@brief PredicPoint�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/18:07
@author mimuro
*/

#include "PredictPoint.h"

/*!
@brief nowPoint��X,Y������nowVelocity��X,Y�����𑫂������W��Ԃ��B
@date 2020/05/04/18:09
@author mimuro
*/
Dimention PredictPoint::calcPredictPoint(Dimention nowPoint, Dimention nowVelocity)
{
	Dimention returnPoint = nowPoint;

	returnPoint.x += nowVelocity.x;
	returnPoint.y += nowVelocity.y;

	return returnPoint;

}

/*!
@brief nowPoint���琅��������predictRange���ɏ�ǂ�����Ȃ�A���̏�ǂɍ��킹��X���W��Ԃ��B
@date 2020/05/04/18:13
@author mimuro
*/
int PredictPoint::fittingPointHorizon(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	// predictRange�����݈ʒu���E��������
	if (predictRange > 0) {
		// predictRange���E�Ƀu���b�N�����邩�ǂ����H
		bool isCollisionedPredictRight = _collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::right, predictRange);
		if (isCollisionedPredictRight) {
			// ������������A�E�̃u���b�N���ӂɍ��킹��B�i���S���W��Ԃ��̂ŁAgetRange�������j
			return getForwardBlockNearSideHorizon(nowPoint, predictRange, _collision, _stage) - _collision->getRange(CollisionDetect::toShiftDirect::right);
		}
	}

	// predictRange�����݈ʒu��荶��������
	if (predictRange < 0) {
		bool isCollisionedPredictLeft = _collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::left, predictRange);
		if (isCollisionedPredictLeft) {
			// ������������A���̃u���b�N�E�ӂɍ��킹��B�i���S���W��Ԃ��̂ŁAgetRange�������j
			return getForwardBlockNearSideHorizon(nowPoint, predictRange, _collision, _stage) + _collision->getRange(CollisionDetect::toShiftDirect::left);
		}
	}
	// �����A�E���ǂɂԂ����Ă��āA�E�𒲂ׂ�悤��������A���W��ς��Ȃ��B
	if (_collision->getCollisionedSide().right && predictRange > 0)
		return nowPoint.x;

	// �����A�����ǂɂԂ����Ă��āA���𒲂ׂ�悤��������A���W��ς��Ȃ��B
	if (_collision->getCollisionedSide().left && predictRange < 0)
		return nowPoint.x;
	// �ȏ�̏����ɓ��Ă͂܂�Ȃ�������predictRange�Ɉړ����Ă��悢�B
	return nowPoint.x + predictRange;
}

/*!
@brief nowPoint���琂��������predictRange���ɏ�ǂ�����Ȃ�A���̏�ǂɍ��킹��Y���W��Ԃ��B
@date 2020/05/04/18:013
@author mimuro
*/
int PredictPoint::fittingPointVertical(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{

	// �����A�����ǂɂԂ����Ă��āA���𒲂ׂ�悤��������A���W��ς��Ȃ��B
	if(_collision->getCollisionedSide().bottom && predictRange > 0)
		return nowPoint.y;

	// �����A�オ�ǂɂԂ����Ă��āA��𒲂ׂ�悤��������A���W��ς��Ȃ��B
	if (_collision->getCollisionedSide().head && predictRange < 0)
		return nowPoint.y;

	// predictY�����݈ʒu��艺��������
	if (predictRange > 0) {
		// predictRange�����Ƀu���b�N�����邩�ǂ����H
		bool isCollisionedPredictBottom = _collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::bottom, predictRange);
		if (isCollisionedPredictBottom) {
			// ������������A���̃u���b�N��ӂɍ��킹��B�i���S���W��Ԃ��̂ŁAgetRange�������j
			return getForwardBlockNearSideVertical(nowPoint, predictRange, _collision, _stage) - _collision->getRange(CollisionDetect::toShiftDirect::bottom);
		}
	}

	// predictY�����݈ʒu���ゾ������
	if (predictRange < 0) {
		bool isCollisionedPredictHead = _collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::head, predictRange);
		if (isCollisionedPredictHead) {
			// ������������A��̃u���b�N���ӂɍ��킹��B�i���S���W��Ԃ��̂ŁAgetRange�������j
			return getForwardBlockNearSideVertical(nowPoint, predictRange, _collision, _stage) + _collision->getRange(CollisionDetect::toShiftDirect::head);
		}
	}

	// �ȏ�̏����ɓ��Ă͂܂�Ȃ�������predictRange�Ɉړ����Ă��悢�B
	return nowPoint.y + predictRange;
}

/*!
@brief predictRange���̈�ԋ߂��u���b�N�̋߂��ӂ�Y���W��Ԃ��B
@date 2020/05/04/18:15
@author mimuro
*/
int PredictPoint::getForwardBlockNearSideVertical(
	Dimention nowPoint,
	int predictRange,
	std::shared_ptr<CollisionDetect> _collision,
	std::shared_ptr<Stage> _stage
)
{
	// predictRange����������������
	if (predictRange > 0)
	{
		// �����{predictRange�̍��W���v�Z
		int x = nowPoint.x;
		int y = nowPoint.y + _collision->getRange(CollisionDetect::toShiftDirect::bottom) + Define::blockHeight;
		// ���̍��W�ɂ���u���b�N�̏�ӂ̂����W��Ԃ��B�i���S���W��Ԃ��̂ŁAgetRange�������j
		return _stage->getBlockCell(x, y).y1;
	}
	// predictRange���������������
	if (predictRange < 0) {
		// ����{predictRange�̍��W���v�Z
		int x = nowPoint.x;
		int y = nowPoint.y - _collision->getRange(CollisionDetect::toShiftDirect::head) - Define::blockHeight;
		// ���̍��W�ɂ���u���b�N�̉��ӂ̂����W��Ԃ��B
		return _stage->getBlockCell(x, y).y2;
	}
	// predictRange��0�������瓯�����W��Ԃ��B

	return nowPoint.y;
}

/*!
@brief predictRange���̈�ԋ߂��u���b�N�̋߂��ӂ�X���W��Ԃ��B
@date 2020/05/04/18:15
@author mimuro
*/
int PredictPoint::getForwardBlockNearSideHorizon(
	Dimention nowPoint,
	int predictRange,
	std::shared_ptr<CollisionDetect> _collision,
	std::shared_ptr<Stage> _stage
)
{
	// predictRange���E������������
	if (predictRange > 0)
	{
		// �E���Ӂ{predictRange�̍��W���v�Z
		int x = nowPoint.x + _collision->getRange(CollisionDetect::toShiftDirect::right) + predictRange;
		int y = nowPoint.y;
		// ���̍��W�ɂ���u���b�N�̍��ӂ�x���W��Ԃ��B
		return _stage->getBlockCell(x, y).x1;
	}
	// predictRange����������������
	if (predictRange < 0) {
		// �����Ӂ{predictRange(predictRange�͕�)�̍��W���v�Z
		int x = nowPoint.x - _collision->getRange(CollisionDetect::toShiftDirect::left) + predictRange;
		int y = nowPoint.y;
		// ���̍��W�ɂ���u���b�N�̉E�ӂ�x���W��Ԃ��B
		return _stage->getBlockCell(x, y).x2;
	}
	// predictRange��0�������瓯�����W��Ԃ��B

	return nowPoint.y;
}

/*!
@brief �󂯎����nowPoint�̊e������fittingPoint�����������ĕԂ��B
@date 2020/05/04/18:17
@author mimuro
*/
Dimention PredictPoint::update(Dimention _nowPoint, Dimention nowVelocity, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{

	nowPoint = _nowPoint;

	predictPoint.x = fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage);

	predictPoint.y = fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage);

	return predictPoint;
}