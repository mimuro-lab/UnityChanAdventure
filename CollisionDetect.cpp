
/*!
@file CollisionDetect.cpp
@brief CollisionDetectクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/05/04/16:36
@author mimuro
*/

#include "CollisionDetect.h"

/*!
@par 頭上・足元・右側・左側の当たり判定を調べる関数。何もreturnしない。
@date 2020/05/04/16:40
@author mimuro
*/
void CollisionDetect::update(Define::Status __nowStatus, std::shared_ptr<Stage> __stage)
{

	Define::Status statusForInside = __nowStatus;
	//上のめり込みを調べる
	statusForInside._y++;

	collisionedInSide.head = detectHead(__stage, statusForInside);

	statusForInside._y--;

	//下のめり込みを調べる
	statusForInside._y--;

	collisionedInSide.bottom = detectBottom(__stage, statusForInside);

	statusForInside._y++;
	//右のめり込みを調べる
	statusForInside._x++;

	collisionedInSide.right = detectHead(__stage, statusForInside);

	statusForInside._x--;

	//左のめり込みを調べる
	statusForInside._x--;

	collisionedInSide.left = detectBottom(__stage, statusForInside);

	statusForInside._x++;

	_stage = __stage;
	nowStatus = __nowStatus;

	collisionedSide.head = detectHead(__stage, __nowStatus);

	collisionedSide.bottom = detectBottom(__stage, __nowStatus);

	// もし、下か上にめり込んでいたら、左右の当たり判定はなし。（めり込んだ状態で更新されるから絶対に当たった判定になってしまう）
	if (!collisionedInSide.bottom ) {

		collisionedSide.right = detectRight(__stage, __nowStatus);

		collisionedSide.left = detectLeft(__stage, __nowStatus);
	}
	else {
		printfDx("");
	}
}

vector<vector<Dimention>> CollisionDetect::getCollisionPoints()
{
	vector<vector<Dimention>> returnPoints;

	Dimention initCell;
	initCell.x = initCell.y = 0;

	vector<Dimention> Head(headPoints+1, initCell);
	returnPoints.push_back(Head);

	vector<Dimention> Bottom(bottomPoints+1, initCell);
	returnPoints.push_back(Bottom);

	vector<Dimention> Right(rightPoints+1, initCell);
	returnPoints.push_back(Right);

	vector<Dimention> Left(leftPoints+1, initCell);
	returnPoints.push_back(Left);



	//head
	for (int i = 0; i < headPoints; i++) {
		// ブロックは0 ～ blockHeight - 1単位で生成されるので、左側を調べる際は-1する
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
		returnPoints[0][i].x = x;
		returnPoints[0][i].y = y;
	}
	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y - toHead - 1;
	returnPoints[0][headPoints].x = x;
	returnPoints[0][headPoints].y = y;

	//bottom
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y + toBottom;
		returnPoints[1][i].x = x;
		returnPoints[1][i].y = y;
	}

	x = nowStatus._x + toRight - 1;
	y = nowStatus._y + toBottom;
	returnPoints[1][bottomPoints].x = x;
	returnPoints[1][bottomPoints].y = y;

	//right
	for (int i = 0; i <= rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		returnPoints[2][i].x = x;
		returnPoints[2][i].y = y;
	}
	x = nowStatus._x + toRight;
	y = nowStatus._y + toBottom - 1;
	returnPoints[2][rightPoints].x = x;
	returnPoints[2][rightPoints].y = y;

	//left
	for (int i = 0; i <= leftPoints; i++) {
		// ブロックは0 ～ blockWidth - 1単位で生成されるので、左側を調べる際は-1する
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		returnPoints[3][i].x = x;
		returnPoints[3][i].y = y;
	}
	x = nowStatus._x - toLeft - 1;
	y = nowStatus._y + toBottom - 1;
	returnPoints[3][leftPoints].x = x;
	returnPoints[3][leftPoints].y = y;

	return returnPoints;
}

/*!
@par 右側の当たり判定を調べる関数。障壁があったらtrueを返す。
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectRight(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i <= rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		if (IsDetectedStage(x, y, stage)) 
			return true;
	}
	int x = nowStatus._x + toRight;
	int y = nowStatus._y + toBottom - 1;
	if (IsDetectedStage(x, y, _stage))
		return true;
	return false;
}

/*!
@par 左側の当たり判定を調べる関数。障壁があったらtrueを返す。
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectLeft(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i <= leftPoints; i++) {
		// ブロックは0 ～ blockWidth - 1単位で生成されるので、左側を調べる際は-1する
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		if (IsDetectedStage(x, y, stage)) 
			return true;
	}
	int x = nowStatus._x - toLeft - 1;
	int y = nowStatus._y + toBottom - 1;
	if (IsDetectedStage(x, y, _stage))
		return true;
	return false;
}

/*!
@par 頭上の当たり判定を調べる関数。障壁があったらtrueを返す。
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectHead(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i < headPoints; i++) {
		// ブロックは0 ～ blockHeight - 1単位で生成されるので、左側を調べる際は-1する
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
		if (IsDetectedStage(x, y, stage))
			return true;
	}
	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y - toHead - 1;
	if (IsDetectedStage(x, y, stage))
		return true;
	return false;
}
/*!
@par 足元の当たり判定を調べる関数。障壁があったらtrueを返す。
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectBottom(shared_ptr<Stage> stage, Status nowStatus)
{
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y + toBottom;
		if (IsDetectedStage(x, y, stage)) 
			return true;
	}

	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y + toBottom;
	if (IsDetectedStage(x, y, stage))
		return true;
	return false;
}

/*!
@par 当たり判定の描画を行う関数。何も返さない。
@date 2020/05/04/16:40
@author mimuro
*/
void CollisionDetect::draw()
{
	// head
	for (int i = 0; i <= headPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	int x = nowStatus._x + toRight - 1;
	int y = nowStatus._y - toHead - 1;
	unsigned int color = GetColor(0, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor(255,0,  0);
	DrawCircle(x, y, 2, color, false);

	// bottom
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / bottomPoints) * i;
		int y = nowStatus._y + toBottom;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255,0,  0);
		DrawCircle(x, y, 2, color, false);
	}
	x = nowStatus._x + toRight - 1;
	y = nowStatus._y + toBottom;
	color = GetColor(255, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor( 255,0, 0);
	DrawCircle(x, y, 2, color, false);
	

	// right
	for (int i = 0; i < rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	x = nowStatus._x + toRight;
	y = nowStatus._y + toBottom - 1;
	color = GetColor(255, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor(255, 0, 0);
	DrawCircle(x, y, 2, color, false);

	// left
	for (int i = 0; i <= leftPoints; i++) {
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y, _stage))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	x = nowStatus._x - toLeft - 1;
	y = nowStatus._y + toBottom - 1;
	color = GetColor(255, 255, 255);
	if (IsDetectedStage(x, y, _stage))
		color = GetColor(0, 255, 0);
	DrawCircle(x, y, 2, color, false);
}

/*!
@par x,y座標にステージのブロックがあるかどうか。
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::IsDetectedStage(int x, int y, shared_ptr<Stage> stage)
{
	// x, y座標がステージのどのインデックスに値するか？
	unsigned char _CellXNum = (x - stage->getPointLeftUpX()) / stage->getBlockWidth() - stage->getAbsIndInitDrawingLeftUpX();
	unsigned char _CellYNum = (y - stage->getPointLeftUpY()) / stage->getBlockHeight() - stage->getAbsIndInitDrawingLeftUpY();

	//ステージ台からはみ出るなら壁に衝突したということ。
	if (_CellXNum < 0 || _CellYNum < 0 || _CellXNum >= stage->getBlockXNum() || _CellYNum >= stage->getBlockYNum()) {
		return false;
	}

	// もし、x, yにあるステージの要素がblockだったら衝突と判定。
	if (stage->getStage()[_CellXNum][_CellYNum]._status == Define::BlockCell::cellStatus::block) {
		return true;
	}

	// どこにも衝突しなければfalseを返す。
	return false;
}

/*!
@par 垂直方向において、_toの方向に_range分先に障壁があるかどうかを判断する関数。
@brief _rangeが1ブロック長を超えていたら、_toの方向から_rangeまでの間もブロックの有無を判定する。
@date 2020/05/04/16:57
@author mimuro
*/
bool CollisionDetect::calcShitingCollisionedSideVertical(toShiftDirect _to, char _range, char _horizonal_range)
{
	isCollisionedEdge = false;
	// 角のx座標
	int edge_x = nowStatus._x;
	// 右向きなら
	if (_horizonal_range > 0) {
		edge_x = nowStatus._x + toRight + std::abs(_horizonal_range);
	}
	else if (_horizonal_range < 0) {
		edge_x = nowStatus._x - toLeft - std::abs(_horizonal_range);
	}

	// rangeが0だったら1先を調べる
	if (_range == 0) {
		switch (_to) {
			case toShiftDirect::head:
				for (int i = 0; i <= headPoints; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y - toHead - 1;
					if (IsDetectedStage(x, y, _stage)) 
						return true;
				}
				return false;
				break;
			case toShiftDirect::bottom:
				for (int i = 0; i < bottomPoints - 1; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y + toBottom + 1;
					if (IsDetectedStage(x, y, _stage))
						return true;
				}
				return false;
				break;
		}
		return false;
	}

	// _rangeがブロックの幅を超えてしまっていたら、プレイヤーオブジェクトのBottonから_stage->blockHeight分ずつ壁の有無を調べる。

	unsigned char BlocksIn_range = 1;//_rangeの中にいくつのブロックが入るか？

	if (_range > _stage->blockHeight)
		BlocksIn_range = _range / _stage->blockHeight;

	switch (_to) {
	case toShiftDirect::head:
		// _rangeの中に障壁がないか調べる。BlocksIn_rangeを用いる。
		for (int block = 0; block < BlocksIn_range; block++) {

			for (int i = 0; i < headPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y - toHead - block * _stage->blockHeight - std::abs(_range);
				//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			int x = nowStatus._x + toRight - 1;
			int y = nowStatus._y - toHead - block * _stage->blockHeight - std::abs(_range);
			//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(x, y, _stage))
				return true;

			// 角を調べる
			//DrawCircle(edge_x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(edge_x, y, _stage)) {
				isCollisionedEdge = true;
				//return true;
			}
		}
		return false;
		break;
	case toShiftDirect::bottom:
		// _rangeの中に障壁がないか調べる。BlocksIn_rangeを用いる。
		for (int block = 0; block < BlocksIn_range; block++) {
			for (int i = 0; i < bottomPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y + toBottom + block * _stage->blockHeight + std::abs(_range);
				//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
				if (IsDetectedStage(x, y, _stage)) {
					collisionSideRange.bottom = block * _stage->blockHeight;
					return true;
				}
			}	
			int x = nowStatus._x + toRight - 1;
			int y = nowStatus._y + toBottom + block * _stage->blockHeight + std::abs(_range);
			//DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(x, y, _stage))
				return true;
			// 角を調べる
			//DrawCircle(edge_x, y, 3, GetColor(255, 255, 255), true);
			if (IsDetectedStage(edge_x, y, _stage)) {
				isCollisionedEdge = true;
				//return true;
			}
		}
		return false;
		break;
	}
	
	//エラー処理、とりあえずぶつかっている事にする。calcShitingCollisionedSideHorizon
	return true;
}

/*!
@par 水平方向において、_toの方向に_range分先に障壁があるかどうかを判断する関数。
@brief _rangeが1ブロック長を超えていたら、_toの方向から_rangeまでの間もブロックの有無を判定する。
@date 2020/05/04/16:58
@author mimuro
*/
bool CollisionDetect::calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range, char _vertical_range)
{
	// 角のy座標
	int edge_y = nowStatus._y;
	isCollisionedEdge = false;
	// 下向きなら
	if (_vertical_range > 0) {
		edge_y = nowStatus._y + toBottom + std::abs(_vertical_range);
	}
	// 上向きなら
	else if (_vertical_range < 0) {
		edge_y = nowStatus._y - toHead - std::abs(_vertical_range);
	}

	// rangeが0だったら、1先の座標を調べる。
	if (_range == 0) {
		switch (_to) {
		case CollisionDetect::toShiftDirect::left:
				for (int i = 0; i < leftPoints - 1; i++) {
					int x = nowStatus._x - toLeft - 1;
					int senceHeight = (toHead + toBottom) / rightPoints;
					int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
					if (IsDetectedStage(x, y, _stage))
						return true;
				}
			break;
		case CollisionDetect::toShiftDirect::right:
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			break;
		}
	}

	Status calcStatus;

	// _rangeがブロックの幅を超えてしまっていたら、プレイヤーオブジェクトのBottonから_stage->blockWidth分ずつ壁の有無を調べる。
	unsigned char BlocksIn_range = 1;//_rangeの中にいくつのブロックが入るか？

	if (std::abs(_range) > _stage->blockWidth)
		BlocksIn_range = std::abs(_range) / _stage->blockWidth + 1;

	switch (_to) {
	case toShiftDirect::right:
		// _rangeの中に障壁がないか調べる。BlocksIn_rangeを用いる。
		for (int block = 0; block < BlocksIn_range; block++) {
			for (int i = 0; i < rightPoints; i++) {
				int x = nowStatus._x + toRight + _range + Define::blockWidth * block;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i;
				//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			int x = nowStatus._x + toRight + std::abs(_range) - Define::blockWidth * block;
			int y = nowStatus._y + toBottom - 1;
			//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y, _stage))
				return true;

			//角を調べる
			//DrawCircle(x, edge_y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, edge_y, _stage)) {
				//return true;
				isCollisionedEdge = true;
			}
		}
		break;

	case toShiftDirect::left:
		// _rangeの中に障壁がないか調べる。BlocksIn_rangeを用いる。
		for (int block = 0; block < BlocksIn_range; block++) {
			for (int i = 0; i < leftPoints; i++) {
				int x = nowStatus._x - toLeft - std::abs(_range) - Define::blockWidth * block;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i;
				//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
				if (IsDetectedStage(x, y, _stage))
					return true;
			}
			int x = nowStatus._x - toLeft - std::abs(_range) - Define::blockWidth * block;
			int y = nowStatus._y + toBottom - 1;
			//DrawCircle(x, y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y, _stage))
				return true;

			//角を調べる
			//DrawCircle(x, edge_y, 3, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, edge_y, _stage)) {
				//return true;
				isCollisionedEdge = true;
			}
		}
		break;
	}

	//エラー処理、とりあえずぶつかっている事にする。
	return false;
}

/*!
@par _toの方向の、中心座標からの当たり判定の範囲を返す関数。
@date 2020/05/04/16:59
@author mimuro
*/
const char CollisionDetect::getRange(toShiftDirect _to)
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
	}
	return 0;
}