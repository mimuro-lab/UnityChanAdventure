
/*!
@file imagePath.h
@brief imagePathクラスが定義されているヘッダファイル
@date 2020/04/18/23:09
@author mimuro
*/

#pragma once
#include "Singleton.h"
#include <vector>

using namespace std;
/*!
@class imagePath
@brief 使用する画像のパスをまとめて管理するクラス。Singletonクラスになっている。
@date 2020/04/16/20:00
@author mimuro
*/
class imagePath : 
	public Singleton<imagePath>
{
	imagePath() = default;
	friend Singleton< imagePath >;
public:

	//! unityChan_BasicActionの画像へのパスをまとめた変数。
	const vector<int> unityChan_Brake = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_2.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_3.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_4.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_5.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_6.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_7.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_8.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_9.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_10.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_11.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_12.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_13.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_14.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_15.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_16.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Brake_17.png"),
	};

	const vector<int> unityChan_Crouch = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Crouch_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Crouch_2.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Crouch_3.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Crouch_4.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Crouch_5.png"),
	};

	const vector<int> unityChan_Damage = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_1.png"),

		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_2.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_3.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_4.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_5.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_6.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_7.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_8.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_9.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_10.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_11.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_12.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_13.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_14.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_15.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_16.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_17.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_18.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Damage_19.png"),
	};

	const vector<int> unityChan_Idle = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Idle_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Idle_2.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Idle_3.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Idle_4.png"),
	};

	const vector<int> unityChan_Jump_Fall = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_Fall_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_Fall_2.png"),
	};

	const vector<int> unityChan_Jump_Landing = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_Landing.png"),
	};

	const vector<int> unityChan_Jump_MidAir = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_MidAir_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_MidAir_2.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_MidAir_3.png"),
	};

	const vector<int> unityChan_Jump_Up = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_Up_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Jump_Up_2.png"),
	};

	const vector<int> unityChan_Run = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_2.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_3.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_4.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_5.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_6.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_7.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_8.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_9.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_10.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_11.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_12.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_13.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_14.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_15.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_16.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_17.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Run_18.png"),
	};

	const vector<int> unityChan_Walk = {
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_1.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_2.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_3.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_4.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_5.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_6.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_7.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_8.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_9.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_10.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_11.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_12.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_13.png"),
		LoadGraph("images/Unitychan/BasicActions/Unitychan_Walk_14.png"),
	};
};
