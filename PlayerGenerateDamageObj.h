#pragma once



#include "Define.h"
#include "Stage.h"
#include "Sword.h"
#include "AbsDamageObj.h"
#include <memory>
#include <vector>

using namespace Define;
using namespace std;

vector<shared_ptr<AbsDamageObj>> Sword1(Status playerStatus, shared_ptr<Stage> stage, shared_ptr<Animation> animation, vector<shared_ptr<AbsDamageObj>> _nowDmg)
{

	vector<shared_ptr<AbsDamageObj>> returnDmg = _nowDmg;

	int initShiftX = 0;
	int initShiftY = 0;


	if (animation->getNowDrawingImageIndex() == 4) {
		if (animation->getDrawingStepsCounter() == 1) {

			initShiftX = 0;
			if (playerStatus.directRight)
				initShiftX = 18;
			else
				initShiftX = -18;
			initShiftY = 17;

			shared_ptr<AbsDamageObj> pushObj = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj);

		}
	}
	if (animation->getNowDrawingImageIndex() == 4) {
		if (animation->getDrawingStepsCounter() == 1) {

			initShiftX = 0;
			if (playerStatus.directRight)
				initShiftX = 25;
			else
				initShiftX = -25;
			initShiftY = 14;

			shared_ptr<AbsDamageObj> pushObj = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj);

		}
	}
	if (animation->getNowDrawingImageIndex() == 4) {
		if (animation->getDrawingStepsCounter() == 1) {

			initShiftX = 0;
			if (playerStatus.directRight)
				initShiftX = 30;
			else
				initShiftX = -30;
			initShiftY = 10;

			shared_ptr<AbsDamageObj> pushObj = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj);

		}
	}

	if (animation->getNowDrawingImageIndex() == 4) {
		if (animation->getDrawingStepsCounter() == 1) {

			initShiftX = 0;
			if (playerStatus.directRight)
				initShiftX = 25;
			else
				initShiftX = -25;
			initShiftY = 2;

			shared_ptr<AbsDamageObj> pushObj = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj);

		}
	}

	return returnDmg;
}

vector<shared_ptr<AbsDamageObj>> Sword2(Status playerStatus, shared_ptr<Stage> stage, shared_ptr<Animation> animation, vector<shared_ptr<AbsDamageObj>> _nowDmg)
{

	vector<shared_ptr<AbsDamageObj>> returnDmg = _nowDmg;

	int initShiftX = 0;
	int initShiftY = 0;

	if (animation->getNowDrawingImageIndex() == 3) {
		if (animation->getDrawingStepsCounter() == 1) {
			initShiftX = 0;
			if (playerStatus.directRight)
				initShiftX = 35;
			else
				initShiftX = -35;
			initShiftY = 10;

			shared_ptr<AbsDamageObj> pushObj1 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj1);
		}
	}

	if (animation->getNowDrawingImageIndex() == 3) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 30;
			else
				initShiftX = -30;
			initShiftY = 14;

			shared_ptr<AbsDamageObj> pushObj2 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj2);
		}
	}


	if (animation->getNowDrawingImageIndex() == 3) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 23;
			else
				initShiftX = -23;
			initShiftY = 17;

			shared_ptr<AbsDamageObj> pushObj3 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj3);
		}
	}


	if (animation->getNowDrawingImageIndex() == 3) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 38;
			else
				initShiftX = -38;
			initShiftY = 0;

			shared_ptr<AbsDamageObj> pushObj4 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj4);
		}
	}


	if (animation->getNowDrawingImageIndex() == 4) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 35;
			else
				initShiftX = -35;
			initShiftY = -10;

			shared_ptr<AbsDamageObj> pushObj5 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj5);
		}
	}


	if (animation->getNowDrawingImageIndex() == 5) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 25;
			else
				initShiftX = -25;
			initShiftY = -20;

			shared_ptr<AbsDamageObj> pushObj6 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj6);
		}
	}

	return returnDmg;
}

vector<shared_ptr<AbsDamageObj>> Sword3(Status playerStatus, shared_ptr<Stage> stage, shared_ptr<Animation> animation, vector<shared_ptr<AbsDamageObj>> _nowDmg)
{
	vector<shared_ptr<AbsDamageObj>> returnDmg = _nowDmg;

	int initShiftX = 0;
	int initShiftY = 0;

	if (animation->getNowDrawingImageIndex() == 6) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 52;
			else
				initShiftX = -52;
			initShiftY = 14;

			shared_ptr<AbsDamageObj> pushObj2 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj2);
		}
	}

	if (animation->getNowDrawingImageIndex() == 7) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 54;
			else
				initShiftX = -54;
			initShiftY = 25;

			shared_ptr<AbsDamageObj> pushObj3 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj3);
		}
	}

	if (animation->getNowDrawingImageIndex() == 5) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 48;
			else
				initShiftX = -48;
			initShiftY = 0;

			shared_ptr<AbsDamageObj> pushObj4 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj4);
		}
	}

	if (animation->getNowDrawingImageIndex() == 4) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 43;
			else
				initShiftX = -43;
			initShiftY = -10;

			shared_ptr<AbsDamageObj> pushObj5 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj5);
		}
	}

	if (animation->getNowDrawingImageIndex() == 4) {
		if (animation->getDrawingStepsCounter() == 1) {
			if (playerStatus.directRight)
				initShiftX = 33;
			else
				initShiftX = -33;
			initShiftY = -20;

			shared_ptr<AbsDamageObj> pushObj6 = make_shared<Sword>(stage, playerStatus._x + initShiftX, playerStatus._y + initShiftY, playerStatus.directRight);

			returnDmg.push_back(pushObj6);
		}
	}

	return returnDmg;
}