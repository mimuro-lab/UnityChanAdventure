#pragma once
#include <DxLib.h>
#include "Keyboard.h"
#include "Singleton.h"

#include <vector>

class Controller final:
	public Singleton<Controller>,
	private Keyboard
{
	Controller() = default;
	friend Singleton< Controller >;

	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
	bool start = false;
	bool select = false;
	bool push_A = false;
	bool push_B = false;
	bool push_X = false;
	bool push_Y = false;

public:
	void update();

	const bool getRight() { return right; }
	const bool getLeft() { return left; }
	const bool getUp() { return up; }
	const bool getDown() { return down; }
	const bool getSelect() { return select; }
	const bool getStart() { return start; }
	const bool getPush_A() { return push_A; }
	const bool getPush_B() { return push_B; }
	const bool getPush_X() { return push_X; }
	const bool getPush_Y() { return push_Y; }

};

