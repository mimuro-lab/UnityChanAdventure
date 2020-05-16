
/*!
@file Player.cpp
@brief Playerクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"

/*!
@brief プレイヤーオブジェクトの座標更新、アニメーションの処理などを行う。
@date 2020/04/21/12:36
@author mimuro
*/
void Player::update(std::shared_ptr<Stage> _stage)
{
	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。
	// Collisionの更新を行う。
	collision->update(playerStatus, _stage);

	// Statusの更新処理を行う。
	playerStatus = animationMove->update(playerStatus, animationSwitch->getNowAction(), collision, _stage, animation);

	// shiftingStageの更新処理も行う。
	shiftingStage = animationMove->getShiftingStage(collision, _stage);

	// アニメーションの下処理を行う。
	animation->update(playerStatus);
	
	// アニメーションの切り替えを行う。もし切り替えなければ同じanimationオブジェクトを返す。
	animation = animationSwitch->update(collision, animation, playerStatus);

	// 方向を更新する。
	playerStatus.directRight = playerDirect->updateDirect(animationSwitch->getNowAction(), playerStatus.directRight, playerStatus);

}

void Player::draw()
{
	animation->draw();
	//collision->draw();

}
