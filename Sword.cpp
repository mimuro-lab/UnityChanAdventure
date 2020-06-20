#include "Sword.h"
#include "ImagePath_Effect.h"

void Sword::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, Status playerStatus)
{

	livingCounter++;

	if (livingCounter < livingTime)
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
	damageStatus = animationMove->update(damageStatus, animationSwitch->getNowAction(), collision, _stage, animation, controller, playerStatus);

	// アニメーションの下処理を行う。
	animation->update(damageStatus);

	animation->arrangeScale(animation->getScale() / 1.2);
	
	damageStatus.directRight = !playerStatus.directRight;
	// アニメーションの切り替えを行う。もし切り替えなければ同じanimationオブジェクトを返す。
	animation = animationSwitch->update(collision, animation, damageStatus, controller);

}

void Sword::draw()
{
	animation->draw();
	//collision->draw();
}

void Sword::adjustBottom(int AdjustRange)
{
	damageStatus._y += AdjustRange;
}
