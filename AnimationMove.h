
/*!
@file AnimationMove.h
@brief AnimationMoveクラスが定義されているヘッダファイル
@date 2020/05/04/14:12
@author mimuro
*/

#pragma once
#include <memory>
#include <vector>
#include "Define.h"
#include "CollisionDetect.h"
#include "Animation.h"
#include "Pysical.h"
#include "PredictPoint.h"
#include "RestrictPoint.h"

/*!
@class AnimationMove
@brief プレイヤーオブジェクトの座標位置を計算するクラス。
@date 2020/05/04/14:16
@author mimuro
*/

using namespace Define;
using namespace std;

class AnimationMove
{
	//! 物理計算を行うオブジェクト。
	Pysical pysical;

	//! 計算された座標が適切であるか予測するオブジェクト。
	PredictPoint predictPoint;

	//! 画面上の動きを制限する。
	RestrictPoint restrictPoint;

	//! 現在の速度を格納する変数。
	Dimention nowVelocity;

	//! 今の座標（更新される前の座標）を格納する変数。
	Dimention nowPoint;

	//! 次の座標（実際に適応される座標）を格納する変数。
	Dimention nextPoint;

public:
	AnimationMove(){
		nowVelocity.x = nowVelocity.y = 0;
	};

	~AnimationMove() = default;
	
	//! 更新を行う関数。
	Status update(Status nowStatus, rollAction_Basic _isAction, shared_ptr<CollisionDetect> _collision, shared_ptr<Stage> _stage, shared_ptr<Animation> _animation);

};

