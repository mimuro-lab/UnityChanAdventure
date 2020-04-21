
/*!
@file Player.cpp
@brief Playerクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"

Player::Player()
{
	playerStatus._x = Define::WIN_W / 2;
	playerStatus._y = Define::WIN_H / 2;
}

/*!
@brief プレイヤーオブジェクトの座標更新、アニメーションの処理などを行う。
@date 2020/04/21/12:36
@author mimuro
*/
void Player::update()
{
	if (Controller::getIns()->getOnRight()) {
		playerStatus._x += 1;
	}

	if (Controller::getIns()->getOnLeft()) {
		playerStatus._x -= 1;
	}

	animation->update(playerStatus._x, playerStatus._y);
	if (animation->isEnd()) {
		animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, playerStatus._x, playerStatus._y);
	}
	
}

void Player::draw()
{
	animation->draw();
}