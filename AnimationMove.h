#pragma once

#include <memory>
#include <vector>
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

	char uptoVel_walk = 5;
	char uptoVel_run = 10;

	std::vector<char> _isInitFroce;
	std::vector<bool> _validGravityAction;
	std::vector<bool> _validStoppingAction;

	class PysicalQTY {

	public:
		enum class vec_Dire{
			head, bottom, right, left, _end,
		};
		char x_vel = 0;
		char x_acc = 0;

		char y_vel = 0;
		char y_acc = 0;

		unsigned short int time = 0;

		unsigned char acc_gravity = 1;
			
		PysicalQTY() = default;
		~PysicalQTY() = default;

		Define::Status update(Define::Status _nowStatus , char _x_acc, char _y_acc, char _initialForceY, char _x_vel_upto, char _y_vel_upto, bool _validGravity, bool _validStopping) {

			Define::Status nextStatus = _nowStatus;

			x_acc = _x_acc;

			if (_validGravity)
				y_acc = _y_acc + acc_gravity;
			else
				y_acc = y_acc;

			if (time == 0) {
				y_vel += _initialForceY;
			}

			if (_x_vel_upto > 0) {
				if (_x_vel_upto >= x_vel + x_acc)
					x_vel += x_acc;
				else if (x_vel + x_acc > _x_vel_upto)
					x_vel = _x_vel_upto;
			}
			else if (_x_vel_upto < 0) {
				if (_x_vel_upto <= x_vel + x_acc)
					x_vel += x_acc;
				else if (x_vel + x_acc < _x_vel_upto)
					x_vel = _x_vel_upto;
			}
			
			if (_validStopping) {
				//右方向に進んでいたら
				if (x_vel > 0) {
					if (_x_vel_upto <= x_vel + x_acc)
						x_vel += x_acc;
					else if (x_vel + x_acc < _x_vel_upto)
						x_vel = _x_vel_upto;
				}
				//左方向に進んでいたら
				if (x_vel < 0) {
					if (_x_vel_upto >= x_vel + x_acc)
						x_vel += x_acc;
					else if (x_vel + x_acc > _x_vel_upto)
						x_vel = _x_vel_upto;
				}
			}

			y_vel += y_acc;

			nextStatus._x += x_vel;
			nextStatus._y += y_vel;

			nextStatus._y_speed = y_vel;
			
			time++;
			
			return nextStatus;
		}

		Define::Status setPoint(Define::Status _nowStatus, int x, int y) {
			time++;
			Define::Status nextStatus = _nowStatus;
			nextStatus._x = x;
			nextStatus._y = y;
			return nextStatus;
		}

		// 今、dire方向に速度が働いているか（入力は調べたい方向）

		bool getShifting(CollisionDetect::toShiftDirect dire, Define::rollAction_Basic _isAction) {

			if (_isAction == Define::rollAction_Basic::Idle)
				return true;

			switch (dire) {
			case CollisionDetect::toShiftDirect::head:
				if (y_vel < 0) return true;
				if (y_vel > 0) return false;
				break;
			case CollisionDetect::toShiftDirect::bottom:
				if (y_vel > 0) return true;
				if (y_vel < 0) return false;
				break;
			case CollisionDetect::toShiftDirect::right:
				if (x_vel > 0) return true;
				if (x_vel < 0) return false;
				break;
			case CollisionDetect::toShiftDirect::left:
				if (x_vel < 0) return true;
				if (x_vel > 0) return false;
				break;
			case CollisionDetect::toShiftDirect::_vertical://垂直に動くべきだったらyの速度方向は関係ない。つまり必ずtrueを返す
				return true;
			}

			switch (dire) {
			case CollisionDetect::toShiftDirect::head:
				if (_isAction == Define::rollAction_Basic::Jump_Up ||
					_isAction == Define::rollAction_Basic::Jump_MidAir)
					return true;
				break;
			case CollisionDetect::toShiftDirect::bottom:
				if (_isAction == Define::rollAction_Basic::Fall ||
					_isAction == Define::rollAction_Basic::Jump_Fall ||
					_isAction == Define::rollAction_Basic::Jump_MidAir)
					return true;
				break;
			case CollisionDetect::toShiftDirect::right:
				if (_isAction == Define::rollAction_Basic::Walk ||
					_isAction == Define::rollAction_Basic::Run)
					return true;
				break;
			case CollisionDetect::toShiftDirect::left:
				if (_isAction == Define::rollAction_Basic::Walk ||
					_isAction == Define::rollAction_Basic::Run)
					return true;
				break;
			}

			return false;

		}

		void refreshVel(bool vertical, bool horizon, bool _time = true) {
			if(vertical)	y_vel = y_acc = 0;
			if(horizon)		x_vel = x_acc = 0;
			if(_time)	time = 0;
		}

	};

	VelocityDEF  velDef;

	PysicalQTY pysicQty;


	CollisionDetect::toShiftDirect getToShift(Define::rollAction_Basic _isAction, Define::Status nowStatus);

	int getForwardBlockNearSide(Define::Status nowStatus, CollisionDetect::toShiftDirect _to, PysicalQTY _pysic, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

	bool getForwardCollisionedSide(CollisionDetect::toShiftDirect _to, std::shared_ptr<CollisionDetect> _collision);

	int getRangeOfNearBlock(CollisionDetect::toShiftDirect _to, PysicalQTY _pysic, std::shared_ptr<CollisionDetect> _collision);

	// [0]がx,[1]がy
	std::vector<char> getAcc(Define::Status nowStatus, Define::rollAction_Basic _isAction, PysicalQTY _pysic);

	char getUptoVelHorizon(Define::Status nowStatus, Define::rollAction_Basic _isAction);

	//	動きが切り替わった瞬間を取得する関数
	Define::rollAction_Basic preIsAction = Define::rollAction_Basic::Idle;
	bool getSwitchAction(Define::rollAction_Basic _isAction) {
		bool ret = false;
		if (_isAction != preIsAction)	ret = true;
		else							ret = false;
		preIsAction = _isAction;
		return ret;
	}

public:
	AnimationMove(char _walk, char _run, char _jumpUp, char _jumpMidAir){
		velDef.basicAction.walk = _walk;
		velDef.basicAction.run = _run;
		velDef.basicAction.jump_up = _jumpUp;
		velDef.basicAction.jump_midAir= _jumpMidAir;
		
		_isInitFroce = std::vector<char>(static_cast<int>(Define::rollAction_Basic::_end), 0);
		_isInitFroce[static_cast<int>(Define::rollAction_Basic::Jump_Up)] = -_jumpUp;
		_isInitFroce[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)] = -_jumpMidAir;

		_validGravityAction= std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validGravityAction[static_cast<int>(Define::rollAction_Basic::Fall)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_Up)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)]
			= true;

		_validStoppingAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validStoppingAction[static_cast<int>(Define::rollAction_Basic::Idle)]
			= true;
	};
	~AnimationMove() = default;

	Define::Status update(Define::Status nowStatus, Define::rollAction_Basic _isAction, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, std::shared_ptr<Animation> _animation);

};

