#pragma once

#include <memory>
#include "Define.h"
#include "CollisionDetect.h"

class AnimationMove
{
	//! 歩く速度
	char speed_walk = 0;
	//! 走る速度
	char speed_run = 0;
	//! Jump_Upの速度
	char jump_up = 0;
	//! Jump_MidAirの速度
	char jump_midAir = 0;

public:
	AnimationMove(char _walk, char _run, char _jumpUp, char _jumpMidAir){
		speed_walk = _walk;
		speed_run = _run;
		jump_up = _jumpUp;
		jump_midAir = _jumpMidAir;
	};
	~AnimationMove() = default;

	//Brake, Crouch, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Fall, Run, Walk,

	Define::Status updateBrake(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateCrouch(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateDamage(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateIdle(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateJump_Fall(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateJump_Landing(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateJump_MidAir(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateJump_Up(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateFall(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateRun(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateWalk(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

};

