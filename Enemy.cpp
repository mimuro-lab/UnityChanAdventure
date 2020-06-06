#include "Enemy.h"

void Enemy::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, std::vector<std::shared_ptr<AbsDamageObj>> _damages)
{

	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。
	// Collisionの更新を行う。
	enemyStatus._y += shiftingStage.y;
	enemyStatus._x += shiftingStage.x;
	collision->update(enemyStatus, _stage);

	// Statusの更新処理を行う。
	enemyStatus = animationMove->update(enemyStatus, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// アニメーションの下処理を行う。
	animation->update(enemyStatus);

	// アニメーションの切り替えを行う。もし切り替えなければ同じanimationオブジェクトを返す。
	animation = animationSwitch->update(collision, animation, enemyStatus, controller);

	// 方向を更新する。
	enemyStatus.directRight = enemyDirect->updateDirect(animationSwitch->getNowAction(), enemyStatus.directRight, enemyStatus, controller);

	if(_damages.size() == 0) {
		isAlive = true;
	}
	else {
		isAlive = false;
	}

}

void Enemy::draw()
{
	animation->draw();
	//collision->draw();
}