#include "PredictStageShift.h"

Dimention PredictStageShift::update(shared_ptr<Stage> stage, shared_ptr<Player> player, Dimention shiftinStage)
{
	Dimention fixedShiftingStage = shiftinStage;
	
	//とりあえず、プレイヤーの底のみを調べる(2020/06/13)
	int playerBottom = player->getStatus()._y + player->getToBottom();
	int predictBottom = playerBottom - shiftinStage.y;

	int deffOfPredictBottomAndBlockHead = 0;

	int centralX = player->getStatus()._x + shiftinStage.x;

	// 中央の底を調べる
	//DrawCircle(centralX, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(centralX, predictBottom - 1, stage)) {//y座標は1上を見る
		int blockHead = stage->getBlockCell(centralX, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead - 2;//計算のための座標は「y座標は1上を見る」のさらに2下（後に引くので下向き）
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		//DrawCircle(centralX, predictBottom, 3, GetColor(0, 255, 0), true);
		//printfDx("fixed\n");
		return fixedShiftingStage;
	}
	
	// 右の底を調べる
	//DrawCircle(centralX + player->getToRight() - 1, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(centralX + player->getToRight() - 1, predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(centralX + player->getToRight() - 1, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead - 2;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		//DrawCircle(centralX + player->getToRight() -1, predictBottom, 3, GetColor(0, 255, 0), true);
		//printfDx("fixed\n");
		return fixedShiftingStage;
	}

	// 左の底を調べる
	//DrawCircle(centralX - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(centralX - player->getToLeft(), predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(centralX - player->getToLeft(), predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead - 2;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		//DrawCircle(centralX - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), true);
		//printfDx("fixed\n");
		return fixedShiftingStage;
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