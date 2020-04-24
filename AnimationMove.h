#pragma once

#include <memory>
#include "Define.h"
#include "CollisionDetect.h"
#include "Animation.h"

class AnimationMove
{
	struct VelocityDEF {
		struct Basic {
			unsigned char walk = 0;
			unsigned char run = 0;
			unsigned char jump_up = 0;
			unsigned char jump_midAir = 0;
		};
		Basic basicAction;
	};


	class PysicalQTY {
	public:
		char x_vel = 0;
		char x_acc = 0;

		char y_vel = 0;
		char y_acc = 0;

		unsigned short int time = 0;
			
		PysicalQTY() = default;
		~PysicalQTY() = default;

		Define::Status update(Define::Status _nowStatus , char _x_acc, char _y_acc) {

			time++;

			Define::Status nextStatus = _nowStatus;

			x_vel += _x_acc;
			y_vel += _y_acc;

			nextStatus._x += x_vel;
			nextStatus._y += y_vel;

			return nextStatus;
		}

		Define::Status setPoint(Define::Status _nowStatus, int x, int y) {
			time++;
			Define::Status nextStatus = _nowStatus;
			nextStatus._x = x;
			nextStatus._y = y;
			return nextStatus;
		}

		void refresh() {
			x_vel = y_vel = x_acc = y_acc = 0;
		}

	};

	VelocityDEF  velDef;

	PysicalQTY pysicQty;

	unsigned char acc_gravity = 1;
	unsigned char div_acc_gravity = 3;
	unsigned char div_acc_gravity_counter = 0;

	unsigned char counter = 0;

public:
	AnimationMove(char _walk, char _run, char _jumpUp, char _jumpMidAir){
		velDef.basicAction.walk = _walk;
		velDef.basicAction.run = _run;
		velDef.basicAction.jump_up = _jumpUp;
		velDef.basicAction.jump_midAir= _jumpMidAir;
	};
	~AnimationMove() = default;

	//Brake, Crouch, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Fall, Run, Walk,

	Define::Status updateBrake(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateCrouch(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateDamage(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateIdle(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateJump_Fall(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateJump_Landing(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateJump_MidAir(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, char steps);
	Define::Status updateJump_Up(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, std::shared_ptr<Animation> _animation);
	Define::Status updateFall(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage,char steps); 
	Define::Status updateRun(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);
	Define::Status updateWalk(Define::Status nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

};

