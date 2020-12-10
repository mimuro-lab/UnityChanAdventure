
/*!
@file Player.cpp
@brief Playerクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"
#include "PlayerGenerateDamageObj.h"

VirtualController Player::updateController()
{
	VirtualController retController;

	retController.on_A = Controller::getIns()->getOn_A();
	retController.on_B = Controller::getIns()->getOn_B();
	retController.on_X = Controller::getIns()->getOn_X();
	retController.on_Y = Controller::getIns()->getOn_Y();

	retController.push_A = Controller::getIns()->getPush_A();
	retController.push_B = Controller::getIns()->getPush_B();
	retController.push_X = Controller::getIns()->getPush_X();
	retController.push_Y = Controller::getIns()->getPush_Y();

	retController.on_right = Controller::getIns()->getOnRight();
	retController.on_left = Controller::getIns()->getOnLeft();
	retController.on_up = Controller::getIns()->getOnUp();
	retController.on_down = Controller::getIns()->getOnDown();

	retController.push_right = Controller::getIns()->getPushRight();
	retController.push_left = Controller::getIns()->getPushLeft();
	retController.push_up = Controller::getIns()->getPushUp();
	retController.push_down = Controller::getIns()->getPushDown();

	return retController;

}

/*!
@brief プレイヤーオブジェクトの座標更新、アニメーションの処理などを行う。
@date 2020/04/21/12:36
@author mimuro
*/
void Player::update(std::shared_ptr<Stage> _stage, std::vector<std::shared_ptr<AbsDamageObj>> _damagesFromEnemys)
{

	if (isEnd) {
		return;
	}

	controller = updateController();

	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。
	// Collisionの更新を行う。
	collision->update(playerStatus, _stage);

	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。
	// Collisionの更新を行う。
	collision->update(playerStatus, _stage);
	collisionPoints = collision->getCollisionPoints();

	bool isDetectedDamages = false;
	
	isDetectedDamages = damagesOverlap->isOverlaped(collisionPoints, _damagesFromEnemys, true/*statusAsPara->isAlive*/);
	
	if (playerStatus.isDamaging) {
		isDetectedDamages = false;
	}

	playerStatus.isDead = !statusAsPara->isAlive;
	
	//printfDx("%d\n", playerStatus.isDead);

	damagesOverlap->refreshDetectedDamageIndex();
	detectDmsInd = damagesOverlap->getDetectedDamageIndex();
	if (isDetectedDamages) {
		for (int i = 0;i < detectDmsInd.size(); i++) {
			DrawFormatString(playerStatus._x, playerStatus._y - 30, GetColor(255, 0, 0), "%d", _damagesFromEnemys[i]->getDamage());
			statusAsPara->acceptDamage(_damagesFromEnemys[i]->getDamage());
		}
	}

	// Statusの更新処理を行う。
	playerStatus = animationMove->update(playerStatus, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// playerStatusのisDamageの更新
	if (statusAsPara->getIsNowDamage()) {
		playerStatus.isDamage = true;
	}else {
		playerStatus.isDamage = false;
	}
	// playerStatusのisDamagingの更新
	if (animationSwitch->getNowAction() == characterAction::Damage) {
		playerStatus.isDamaging = true;
	}else {
		playerStatus.isDamaging = false;
	}

	// shiftingStageの更新処理も行う。
	shiftingStage = animationMove->getShiftingStage(collision, _stage);

	// アニメーションの下処理を行う。
	animation->update(playerStatus);

	if (/*animation->isEnd() &&*/ playerStatus.isDead) {
		isDead = true;
	}
	if (animation->isEnd() && animationSwitch->getNowAction() == characterAction::Death) {
		isEnd = true;
	}
	// アニメーションの切り替えを行う。もし切り替えなければ同じanimationオブジェクトを返す。
	animation = animationSwitch->update(collision, animation, playerStatus, controller);

	// 方向を更新する。
	playerStatus.directRight = playerDirect->updateDirect(animationSwitch->getNowAction(), playerStatus.directRight, playerStatus, controller);

}

/*!
@brief プレイヤーオブジェクトの座標更新、ステージを動かした後に、プレイヤーがめり込むことがある。ステージから押し出す処理。
@date 2020/04/21/12:36
@author mimuro
*/
void Player::pushPlayerFromStage(std::shared_ptr<Stage> _stage)
{
	if (collision->getCollisionedInSide().bottom) {
		
		int y =	_stage->getBlockCell(playerStatus._x, playerStatus._y + collision->getRange(CollisionDetect::toShiftDirect::bottom)).y1;
		y = y + _stage->getPointLeftUpY() - collision->getRange(CollisionDetect::toShiftDirect::bottom);
		playerStatus._y = y ;
		
	}
}

int Player::adjustStageAndBottom(std::shared_ptr<Stage> _stage)
{
	if (collision->getCollisionedInSide().bottom) {
		
		int block_y =	_stage->getBlockCell(playerStatus._x, playerStatus._y + collision->getRange(CollisionDetect::toShiftDirect::bottom)).y1;
		block_y = block_y + _stage->getPointLeftUpY();
		int defBottomAndBlock = playerStatus._y + collision->getRange(CollisionDetect::toShiftDirect::bottom) - block_y;

		return defBottomAndBlock;
		
	}
	return 0;
}

void Player::draw()
{

	// ステータス関係の描画処理
	statusAsPara->draw(playerStatus._x + 20, playerStatus._y - 50, 10, 60);

	animation->draw();
	//collision->draw();

	//DrawFormatString(playerStatus._x, playerStatus._y, GetColor(255, 255, 255), "hp:%d", statusAsPara->HitPoint);
}

vector<shared_ptr<AbsDamageObj>> Player::generateDamageObj(vector<shared_ptr<AbsDamageObj>> _nowDmg, shared_ptr<Stage> stage)
{
	vector<shared_ptr<AbsDamageObj>> returnDmg = _nowDmg;

	if (animationSwitch->getNowAction() == characterAction::Hundgun_horizonal
		&& animation->getNowDrawingImageIndex() == 1
		&& animation->getDrawingStepsCounter() == 1
		) {
		shared_ptr<AbsDamageObj> pushObj = make_shared<Bullet>(stage, playerStatus._x, playerStatus._y, 20, playerStatus.directRight);
		returnDmg.push_back(pushObj);
		//printfDx("%d\n", returnDmg.size());
	}
	
	int ind = animation->getNowDrawingImageIndex();
	int cnt = animation->getDrawingStepsCounter();

	// 剣攻撃1のダメージオブジェクトの生成
	if (animationSwitch->getNowAction() == characterAction::Soard1_init	) {

		returnDmg = Sword1(playerStatus, stage, animation, returnDmg);

	}

	if (animationSwitch->getNowAction() == characterAction::Soard2_init	) {

		returnDmg = Sword2(playerStatus, stage, animation, returnDmg);

	}
		
	if (animationSwitch->getNowAction() == characterAction::Soard3_init	) {

		returnDmg = Sword3(playerStatus, stage, animation, returnDmg);

	}


	return returnDmg;
}