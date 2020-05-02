#pragma once

#include <memory>
#include <vector>
#include "Define.h"
#include "CollisionDetect.h"
#include "Animation.h"
#include "Pysical.h"

class AnimationMove
{

	char uptoVel_walk = 0;
	char uptoVel_run = 0;

	std::vector<char> _isInitFroce;
	std::vector<bool> _validGravityAction;
	std::vector<bool> _validStoppingAction;

	VelocityDEF  velDef;

	Pysical pysic;

	Pysical pysical;


	CollisionDetect::toShiftDirect getToShift(Define::rollAction_Basic _isAction, Define::Status nowStatus);

	int getForwardBlockNearSideVertical(Define::Status nowStatus, CollisionDetect::toShiftDirect _to, Pysical _pysic, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

	int getForwardBlockNearSideHorizon(Define::Status nowStatus, CollisionDetect::toShiftDirect _to, Pysical _pysic, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage);

	bool getForwardCollisionedSide(CollisionDetect::toShiftDirect _to, std::shared_ptr<CollisionDetect> _collision);

	int getRangeOfNearBlock(CollisionDetect::toShiftDirect _to, Pysical _pysic, std::shared_ptr<CollisionDetect> _collision);

	int getRangeOfNearBlockHorizon(CollisionDetect::toShiftDirect _to, Pysical _pysic, std::shared_ptr<CollisionDetect> _collision);

	// [0]Ç™x,[1]Ç™y
	std::vector<char> getAcc(Define::Status nowStatus, Define::rollAction_Basic _isAction, Pysical _pysic);

	char getUptoVelHorizon(Define::Status nowStatus, Define::rollAction_Basic _isAction);

	//	ìÆÇ´Ç™êÿÇËë÷ÇÌÇ¡ÇΩèuä‘ÇéÊìæÇ∑ÇÈä÷êî
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
		velDef.basicAction.walk = uptoVel_walk = _walk;
		velDef.basicAction.run = uptoVel_run = _run;
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

