#include "Enemy.h"

void Enemy::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, std::vector<std::shared_ptr<AbsDamageObj>> _damages)
{
	statusAsChara._y += shiftingStage.y;
	statusAsChara._x += shiftingStage.x;

	if (statusAsChara._x < 0 + deActiveLeft 
		|| statusAsChara._x > WIN_W + deActiveRight
		|| statusAsChara._y < 0 + deActiveHead
		|| statusAsChara._y > WIN_H + deActiveBottom)
		statusAsPara->isActive = false;
	else
		statusAsPara->isActive = true;

	if (!statusAsPara->isActive)
		return;


	// プレイヤーの座標を決定してから当たり判定をする。※順序を逆にするとエラー。
	// Collisionの更新を行う。
	collision->update(statusAsChara, _stage);
	collisionPoints = collision->getCollisionPoints();

	bool isDetectedDamages = false;
	isDetectedDamages = damagesOverlap->isOverlaped(collisionPoints, _damages);
	if(isDetectedDamages)
		DrawCircle(statusAsChara._x, statusAsChara._y, 50, GetColor(255, 255, 255), false);

	// Statusの更新処理を行う。
	statusAsChara = animationMove->update(statusAsChara, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// アニメーションの下処理を行う。
	animation->update(statusAsChara);

	// アニメーションの切り替えを行う。もし切り替えなければ同じanimationオブジェクトを返す。
	animation = animationSwitch->update(collision, animation, statusAsChara, controller);

	// 方向を更新する。
	statusAsChara.directRight = enemyDirect->updateDirect(animationSwitch->getNowAction(), statusAsChara.directRight, statusAsChara, controller);

}

void Enemy::adjustBottom(int AdjustRange)
{
	statusAsChara._y += AdjustRange;
}

void Enemy::draw()
{
	animation->draw();
	//collision->draw();

	//DrawFormatString(statusAsChara._x, statusAsChara._y, GetColor(255, 255, 255), "%d %d", statusAsChara._x, statusAsChara._y);

}