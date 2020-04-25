#include "CollisionDetect.h"

void CollisionDetect::update(Define::Status _nowStatus, std::shared_ptr<Stage> __stage)
{
	nowStatus = _nowStatus;
	_stage = __stage;
	
	collisionedSide.head = detectHead();

	collisionedSide.right = detectRight();

	collisionedSide.bottom = detectBottom();

	collisionedSide.left = detectLeft();

}

bool CollisionDetect::detectHead()
{
	for (int i = 0; i < headPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead;
		if (IsDetectedStage(x, y))
			return true;
	}
	return false;
}

bool CollisionDetect::detectRight()
{
	for (int i = 0; i < headPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		if (IsDetectedStage(x, y)) 
			return true;
	}
	return false;
}

bool CollisionDetect::detectBottom()
{
	for (int i = 0; i < rightPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y + toBottom;
		if (IsDetectedStage(x, y)) 
			return true;
	}
	return false;
}

bool CollisionDetect::detectLeft()
{
	for (int i = 0; i < leftPoints; i++) {
		int x = nowStatus._x - toLeft;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		if (IsDetectedStage(x, y)) 
			return true;
	}
	return false;
}

void CollisionDetect::draw()
{
	// head
	for (int i = 0; i < headPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}

	// bottom
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / bottomPoints) * i;
		int y = nowStatus._y + toBottom;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	
	// right
	for (int i = 0; i < rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}

	// left
	for (int i = 0; i < leftPoints; i++) {
		int x = nowStatus._x - toLeft;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	
}

bool CollisionDetect::IsDetectedStage(int x, int y)
{
	// x, y座標がステージのどのインデックスに値するか？
	char _CellXNum = (x - _stage->getPointLeftUpX()) / _stage->getBlockWidth();
	char _CellYNum = (y - _stage->getPointLeftUpY()) / _stage->getBlockHeight();

	//ステージ台からはみ出るなら壁に衝突したということ。
	if (_CellXNum < 0 || _CellYNum < 0 || _CellXNum >= _stage->getBlockXNum() || _CellYNum >= _stage->getBlockYNum()) {
		DrawCircle(x, y, 30, GetColor(0, 255, 255), false);
		return false;
	}

	// もし、x, yにあるステージの要素がblockだったら衝突と判定。
	if (_stage->getStage()[_CellXNum][_CellYNum]._status == Define::BlockCell::cellStatus::block) {
		return true;
	}

	// どこにも衝突しなければfalseを返す。
	return false;
}

// range分さきに障壁があったらtrue
bool CollisionDetect::calcShitingCollisionedSide(toShiftDirect _to, unsigned char _range)
{
	_calcRange = _range;

	if (_calcRange == 0)
		return false;


	if (_to == CollisionDetect::toShiftDirect::bottom || _to == CollisionDetect::toShiftDirect::head || _to == CollisionDetect::toShiftDirect::_vertical) {
		if (_range > _stage->blockHeight)
			_calcRange = _stage->blockHeight;
	}
	else if (_to == CollisionDetect::toShiftDirect::right || _to == CollisionDetect::toShiftDirect::left) {
		if (_range > _stage->blockWidth)
			_calcRange = _stage->blockWidth;
	}

	switch (_to) {
	case toShiftDirect::right:
		return IsDetectedStage(nowStatus._x + _calcRange, nowStatus._y);
		break;
	case toShiftDirect::left:
		return IsDetectedStage(nowStatus._x - _calcRange, nowStatus._y);
		break;
	case toShiftDirect::head:
		for (int i = 0; i < rightPoints; i++) {
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y - toBottom - _calcRange;
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;
	case toShiftDirect::bottom:
		for (int i = 0; i < rightPoints; i++) {
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y + toBottom + _calcRange;
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;
	case toShiftDirect::_vertical://上下しらべる
		for (int i = 0; i < rightPoints; i++) {
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y + toBottom + _calcRange;
			if (IsDetectedStage(x, y))
				return true;
		}
		for (int i = 0; i < rightPoints; i++) {
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y - toBottom - _calcRange;
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;
	}
	
	//エラー処理、とりあえずぶつかっている事にする。
	return true;
}

const char CollisionDetect::getRange(toShiftDirect _to, int y_vel, int x_vel)
{
	switch (_to) {
	case toShiftDirect::head:
		return toHead;
		break;
	case toShiftDirect::bottom:
		return toBottom;
		break;
	case toShiftDirect::right:
		return toRight;
		break;
	case toShiftDirect::left:
		return toLeft;
		break;
	case toShiftDirect::_vertical://垂直だったら座標がどっちに動いているかで判断（速度０はどっちでも構わないが上に合わせる）
		if (y_vel <= 0)
			return toHead;
		else
			return toBottom;
		
	case toShiftDirect::_none:
		return 0;
		break;
	}

	return 0;
}