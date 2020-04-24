#pragma once

#include <memory>
#include "Define.h"
#include "CollisionDetect.h"

class AnimationMove
{
	struct Velocity {
		struct Basic {
			unsigned char walk = 0;
			unsigned char run = 0;
			unsigned char jump_up = 0;
			unsigned char jump_midAir = 0;
		};
		Basic basicAction;
	};

	Velocity  velocity;

public:
	AnimationMove(char _walk, char _run, char _jumpUp, char _jumpMidAir){
		velocity.basicAction.walk = _walk;
		velocity.basicAction.run = _run;
		velocity.basicAction.jump_up = _jumpUp;
		velocity.basicAction.jump_midAir= _jumpMidAir;
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

