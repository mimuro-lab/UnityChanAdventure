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
bool CollisionDetect::calcShitingCollisionedSideVertical(toShiftDirect _to, char _range)
{
	// rangeが0だったら1先を調べる
	if (_range == 0) {
		switch (_to) {
			case toShiftDirect::head:
				for (int i = 0; i <= headPoints; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y - toHead - 1;
					if (IsDetectedStage(x, y)) 
						return true;
				}
				return false;
				break;
		}
		return false;
	}

	if (_to != toShiftDirect::_vertical)
		_range = std::abs(_range);

	collisionSideRange.bottom = collisionSideRange.head = collisionSideRange.right = collisionSideRange.left = 0;
	
	// _rangeがブロックの幅を超えてしまっていたら、プレイヤーオブジェクトのBottonから_stage->blockHeight分ずつ壁の有無を調べる。

	unsigned char BlocksIn_range = 0;//_rangeの中にいくつのブロックが入るか？

	if (_range > _stage->blockHeight)
		BlocksIn_range = _range / _stage->blockHeight;

	switch (_to) {
	case toShiftDirect::head:
		for (int i = 0; i < headPoints; i++) {
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y - toBottom - _range;
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;
	case toShiftDirect::bottom:
		// _rangeの中に障壁がないか調べる。BlocksIn_rangeを用いる。
		for(int block = 0; block < BlocksIn_range; block++)
			for (int i = 0; i < bottomPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y + toBottom + block * _stage->blockHeight; 
				if (IsDetectedStage(x, y)) {
					collisionSideRange.bottom = block * _stage->blockHeight;
					return true;
				}
			}

		DrawBox(nowStatus._x - 20, nowStatus._y - 40, nowStatus._x + 20, nowStatus._y + 40, GetColor(255, 0, 0), false);
		for (int i = 0; i < rightPoints; i++) {	
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y + toBottom + _range;
			DrawCircle(x, y, 3, GetColor(255, 0, 0), false);
			if (IsDetectedStage(x, y)) {
				collisionSideRange.bottom = _range;
				return true;
			}
		}
		return false;
		break;
	case toShiftDirect::_vertical://_rangeの向きによって、上か下を調べる
		//上向きの場合
		if (_range < 0) {
			for (int i = 0; i < headPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y - toBottom - _range;
				if (IsDetectedStage(x, y))
					return true;
			}
		}
		//下向けの場合
		if (_range > 0) {
			for (int block = 0; block < BlocksIn_range; block++)
				for (int i = 0; i < bottomPoints; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y + toBottom + block * _stage->blockHeight;
					if (IsDetectedStage(x, y)) {
						collisionSideRange.bottom = block * _stage->blockHeight;
						return true;
					}
				}

			DrawBox(nowStatus._x - 20, nowStatus._y - 40, nowStatus._x + 20, nowStatus._y + 40, GetColor(255, 0, 0), false);
			for (int i = 0; i < rightPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y + toBottom + _range;
				DrawCircle(x, y, 3, GetColor(255, 0, 0), false);
				if (IsDetectedStage(x, y)) {
					collisionSideRange.bottom = _range;
					return true;
				}
			}
		}
		return false;
		break;
	}
	
	//エラー処理、とりあえずぶつかっている事にする。
	return true;
}

bool CollisionDetect::calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range)
{

	//if (_range == 0)
		//return false;
	// rangeが0だったら、1先の座標を調べる。
	if (_range == 0) {
		switch (_to) {
		case CollisionDetect::toShiftDirect::left:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			break;
		case CollisionDetect::toShiftDirect::right:
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			break;
		case CollisionDetect::toShiftDirect::_none:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		case CollisionDetect::toShiftDirect::bottom:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		case CollisionDetect::toShiftDirect::head:
			for (int i = 0; i < leftPoints - 1; i++) {
				//int x = nowStatus._x - toLeft - 1;
				int y = nowStatus._y - toHead - 1;
				int senceHeight = (toLeft + toRight) / headPoints;
				int x = nowStatus._x - toLeft + senceHeight * i;
				//int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		case CollisionDetect::toShiftDirect::_vertical:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		}
	}

	if (_to != toShiftDirect::_holizen)
		_range = std::abs(_range);

	//collisionSideRange.bottom = collisionSideRange.head = collisionSideRange.right = collisionSideRange.left = 0;

	// _rangeがブロックの幅を超えてしまっていたら、プレイヤーオブジェクトのBottonから_stage->blockWidth分ずつ壁の有無を調べる。
	unsigned char BlocksIn_range = 0;//_rangeの中にいくつのブロックが入るか？

	if (_range > _stage->blockWidth)
		BlocksIn_range = _range / _stage->blockWidth;

	switch (_to) {
	case toShiftDirect::right:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;

	case toShiftDirect::left:
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;

	case toShiftDirect::_holizen://速度によって、右か左を調べる
		if (_range > 0) {
			for (int i = 0; i < rightPoints; i++) {
				int x = nowStatus._x + toRight + _range;
				int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
				if (IsDetectedStage(x, y))
					return true;
			}
		}
		if (_range > 0) {
			for (int i = 0; i < leftPoints; i++) {
				int x = nowStatus._x - toLeft - _range;
				int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
				if (IsDetectedStage(x, y))
					return true;
			}
		}
		return false;
		break;

	case CollisionDetect::toShiftDirect::head:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / leftPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
	case CollisionDetect::toShiftDirect::_vertical:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / leftPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
	case CollisionDetect::toShiftDirect::bottom:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / leftPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
	}

	//エラー処理、とりあえずぶつかっている事にする。
	return false;
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

	case toShiftDirect::_holizen://水平だったら座標がどっちに動いているかで判断（速度０はどっちでも構わないが左に合わせる）
		if (x_vel <= 0)
			return toLeft;
		else
			return toRight;
	case toShiftDirect::_none://停止状態であるべき時は下のブロックに合わせる
		return toBottom;
		break;
	}

	return 0;
}