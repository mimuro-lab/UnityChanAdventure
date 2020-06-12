#include "PredictStageShift.h"

Dimention PredictStageShift::update(shared_ptr<Stage> stage, shared_ptr<Player> player, Dimention shiftinStage)
{
	Dimention fixedShiftingStage = shiftinStage;
	
	//とりあえず、プレイヤーの底のみを調べる(2020/06/13)
	int playerBottom = player->getStatus()._y + player->getToBottom();
	int predictBottom = playerBottom - shiftinStage.y;

	

	int deffOfPredictBottomAndBlockHead = 0;
	

	// 中央の底を調べる
	DrawCircle(player->getStatus()._x, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(player->getStatus()._x, predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(player->getStatus()._x, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		DrawCircle(player->getStatus()._x, predictBottom, 3, GetColor(0, 255, 0), true);
		printfDx("fixed\n");
	}

	// 右の底を調べる
	DrawCircle(player->getStatus()._x + player->getToRight() - 1, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(player->getStatus()._x + player->getToRight() - 1, predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(player->getStatus()._x, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		DrawCircle(player->getStatus()._x + player->getToRight() -1, predictBottom, 3, GetColor(0, 255, 0), true);
		printfDx("fixed\n");
	}

	// 左の底を調べる
	DrawCircle(player->getStatus()._x - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(player->getStatus()._x - player->getToLeft(), predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(player->getStatus()._x, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		DrawCircle(player->getStatus()._x - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), true);
		printfDx("fixed\n");
	}

	return fixedShiftingStage;

}

bool PredictStageShift::IsDetectedStage(int x, int y, shared_ptr<Stage> stage)
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