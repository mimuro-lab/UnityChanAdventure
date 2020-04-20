#include "Player.h"

Player::Player()
{
}

void Player::update()
{

	drawingObj->update(100,100);
	if (drawingObj->isEnd()) {
		drawingObj = std::make_shared<ImageDraw>(imagePath::getIns()->unityChan_Idle, 100, 100);
	}
	
}

void Player::draw()
{
	drawingObj->draw();
}