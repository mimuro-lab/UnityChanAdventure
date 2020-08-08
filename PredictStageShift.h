#pragma once

#include <memory>
#include "Stage.h"
#include "Player.h"
#include "Define.h"

using namespace std;
using namespace Define;

class PredictStageShift
{
public:
	PredictStageShift() {
	}
	~PredictStageShift() = default;

	Dimention update(shared_ptr<Stage> stage, shared_ptr<Player> player, Dimention shiftinStage);

	//! (x, y)À•W‚Í‰½‚©‚É“–‚½‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©
	bool IsDetectedStage(int x, int y, shared_ptr<Stage> stage);
};

