#include "Bullet.h"

void Bullet::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, Status playerStatus)
{
	livingCounter++;

	if (livingCounter < livingTime && !isDetectEnemy)
		isLive = true;
	else
		isLive = false;

	controller.clear();
	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。
	// Collisionの更新を行う。
	damageStatus._y += shiftingStage.y;
	damageStatus._x += shiftingStage.x;
	collision->update(damageStatus, _stage);

	collisionPoints = collision->getCollisionPoints();

	// Statusの更新処理を行う。
	damageStatus = animationMove->update(damageStatus, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// アニメーションの下処理を行う。
	animation->update(damageStatus);

	// アニメーションの切り替えを行う。もし切り替えなければ同じanimationオブジェクトを返す。
	animation = animationSwitch->update(collision, animation, damageStatus, controller);

	// 方向を更新する。
	damageStatus.directRight = damageDirect->updateDirect(animationSwitch->getNowAction(), damageStatus.directRight, damageStatus, controller);

}

void Bullet::draw()
{
	animation->draw();
	//collision->draw();
}

void Bullet::adjustBottom(int AdjustRange)
{
	damageStatus._y += AdjustRange;
}

void Bullet::detectEnemy() {
	isDetectEnemy = true;
}

void Bullet::detectPlayer() {
	isDetectEnemy = true;
}