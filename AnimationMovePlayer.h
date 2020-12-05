#pragma once

#include "AnimationMove.h"
#include "RestrictPoint.h"

class AnimationMovePlayer :
	public AnimationMove
{
	//! 画面上の動きを制限する。
	RestrictPoint restrictPoint;

public:
	AnimationMovePlayer() {}
	~AnimationMovePlayer() = default;

	//! 更新を行う関数。
	Status update(
		Status nowStatus, 
		characterAction _isAction, 
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Stage> _stage, 
		shared_ptr<Animation> _animation, 
		VirtualController controller) override;

	//! ダメージによる更新。
	
	//! shiftingStageの更新を行う関数。
	Dimention getShiftingStage(shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage);
};

