
/*!
@file imagePath.h
@brief imagePathクラスが定義されているヘッダファイル
@date 2020/04/18/23:09
@author mimuro
*/

#pragma once
#include "Singleton.h"
#include <vector>
#include <DxLib.h>

using namespace std;
/*!
@class imagePath
@brief 使用する画像のパスをまとめて管理するクラス。SingletonクラスにSなっている。
@date 2020/04/16/20:00
@author mimuro
*/
class ImagePath_Unitychan : 
	public Singleton<ImagePath_Unitychan>
{
	ImagePath_Unitychan() = default;
	friend Singleton< ImagePath_Unitychan >;
public:

	//! characterActionActionの画像へのパスをまとめた変数。
	const vector<int> unityChan_Brake = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_3.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_4.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_5.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_6.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_7.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_8.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_9.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_10.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_11.png"),
		/*
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_12.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_13.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_14.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_15.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_16.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Brake_17.png"),
		*/
	};

	const vector<int> unityChan_Crouch = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Crouch_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Crouch_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Crouch_3.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Crouch_4.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Crouch_5.png"),
	};
	

	const vector<int> unityChan_Death = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_3.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_4.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_5.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_6.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_7.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_8.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_9.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_10.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_11.png"),
	};


	const vector<int> unityChan_Damage = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_3.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_4.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_5.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_6.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_7.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_8.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_9.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_10.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_11.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_12.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_13.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_14.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_15.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_16.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_17.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_18.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Damage_19.png"),
	};

	const vector<int> unityChan_Idle = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Idle_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Idle_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Idle_3.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Idle_4.png"),
	};

	const vector<int> unityChan_Jump_Fall = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_Fall_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_Fall_2.png"),
	};

	const vector<int> unityChan_Fall = unityChan_Jump_Fall;

	const vector<int> unityChan_Jump_Landing = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_Landing.png"),
	};

	const vector<int> unityChan_Jump_MidAir = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_MidAir_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_MidAir_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_MidAir_3.png"),
	};

	const vector<int> unityChan_Jump_Up = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_Up_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Jump_Up_2.png"),
	};

	const vector<int> unityChan_Run = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_3.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_4.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_5.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_6.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_7.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_8.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_9.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_10.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_11.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_12.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_13.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_14.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_15.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_16.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_17.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Run_18.png"),
	};

	const vector<int> unityChan_Walk = {
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_1.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_2.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_3.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_4.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_5.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_6.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_7.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_8.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_9.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_10.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_11.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_12.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_13.png"),
		LoadGraph("images/Character/UnityChan/BasicActions/UnityChan_Walk_14.png"),
	};

	const vector<int> unityChan_Hundgun_init = {
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_1.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_2.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_3.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_4.png"),
	};

	const vector<int> unityChan_Hundgun_end = {
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_4.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_3.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_2.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun1_1.png"),
	};

	const vector<int> unityChan_Hundgun_horizonal = {
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun2_5.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun2_6.png"),
		//LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun2_7.png"),
		//LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun2_8.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Hundgun2_9.png"),
	};

	const vector<int> unityChan_Soard1_init = {
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_1.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_2.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_3.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_4.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_5.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_6.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_7.png"),
		//LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_7.png"),
	};

	const vector<int> unityChan_Soard2_init = {
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_8.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_9.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_10.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_11.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_12.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_13.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_14.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_15.png"),
	};

	const vector<int> unityChan_Soard3_init = {
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_16.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_17.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_18.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_19.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_20.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_21.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_22.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_23.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_24.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_25.png"),
	};

	const vector<int> unityChan_Soard1_end = {
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_4.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_3.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_2.png"),
		LoadGraph("images/Character/UnityChan/Attack/UnityChan_Soard_Combo_1.png"),
	};

};
