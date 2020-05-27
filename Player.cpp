
/*!
@file Player.cpp
@brief Playerクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"

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
void Player::update(std::shared_ptr<Stage> _stage)
{

	controller = updateController();

	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。
	// Collisionの更新を行う。
	collision->update(playerStatus, _stage);

	// Statusの更新処理を行う。
	playerStatus = animationMove->update(playerStatus, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// shiftingStageの更新処理も行う。
	shiftingStage = animationMove->getShiftingStage(collision, _stage);

	// アニメーションの下処理を行う。
	animation->update(playerStatus);
	
	// アニメーションの切り替えを行う。もし切り替えなければ同じanimationオブジェクトを返す。
	animation = animationSwitch->update(collision, animation, playerStatus, controller);

	// 方向を更新する。
	playerStatus.directRight = playerDirect->updateDirect(animationSwitch->getNowAction(), playerStatus.directRight, playerStatus, controller);

}

void Player::draw()
{
	animation->draw();
	//collision->draw();
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

	if (animationSwitch->getNowAction() == characterAction::Soard1_init
		&& animation->getNowDrawingImageIndex() == 4
		&& animation->getDrawingStepsCounter() == 1
		) {

		int initShiftX = 0;
		if (playerStatus.directRight)
			initShiftX = 30;
		else
			initShiftX = -30;
		int initShiftY = 10;

		shared_ptr<AbsDamageObj> pushObj1 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);
		
		returnDmg.push_back(pushObj1);
		
		initShiftX = 0;
		if (playerStatus.directRight)
			initShiftX = 25;
		else
			initShiftX = -25;
		initShiftY = 14;

		shared_ptr<AbsDamageObj> pushObj2 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

		returnDmg.push_back(pushObj2);

		initShiftX = 0;
		if (playerStatus.directRight)
			initShiftX = 18;
		else
			initShiftX = -18;
		initShiftY = 17;

		shared_ptr<AbsDamageObj> pushObj3 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

		returnDmg.push_back(pushObj3);

		initShiftX = 0;
		if (playerStatus.directRight)
			initShiftX = 25;
		else
			initShiftX = -25;
		initShiftY = 2;

		shared_ptr<AbsDamageObj> pushObj4 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

		returnDmg.push_back(pushObj4);

	}

	return returnDmg;
}