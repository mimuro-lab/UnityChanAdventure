#pragma once
#include "Define.h"
#include "CollisionDetect.h"

enum class vec_Dire {
	head, bottom, right, left, _end,
};

class Pysical {

public:

	char x_vel = 0;	
	char y_vel = 0;

	char x_acc = 0;
	char y_acc = 0;

	unsigned short int time = 0;

	unsigned char acc_gravity = 1;

	Pysical() = default;
	~Pysical() = default;

	Define::Status update(
		Define::Status _nowStatus, 
		char _x_acc, char _y_acc, 
		char _initialForceY, 
		char _x_vel_upto, char _y_vel_upto, 
		bool _validGravity, bool _validStopping);

	Define::Status setPoint(Define::Status _nowStatus, Pysical _pysic, int x, int y);

	// 今、dire方向に速度が働いているか（入力は調べたい方向）

	bool getShifting(CollisionDetect::toShiftDirect dire, Define::rollAction_Basic _isAction);

	void refreshVel(bool vertical, bool horizon, bool _time = true);

	std::vector<int> getVector() {
		std::vector<int> retVec = { x_vel, y_vel };
		return retVec;
	}

	std::vector<int> getAccel() {
		std::vector<int> retAcc = { x_acc, y_acc };
		return retAcc;
	}

};