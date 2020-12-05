#pragma once

/*!
@file Define.h
@brief いろいろな定義をまとまる為のヘッダファイル
@date 2020/04/15/0:19
@author mimuro
*/

/*!
@enum eScene
@brief シーンの定義、クラス名と被らないようにシーンの頭に'e'を付けるようにする。
@date 2020/04/15/16:47
@author mimuro
*/
enum class eScene {
	eNone,
	eStartScene,
	eMenuScene,
	eConfigScene,
	eGameScene,
};

/*!
@class Define
@brief あらゆるパラメータの定義を保持するクラス
@date 2020/04/15/0:19
@author mimuro
*/
#pragma once
namespace Define{

	//! ウィンドウサイズ横
	const static int WIN_W = 1080;

	//! ウィンドウサイズ縦
	const static int WIN_H = 608;
	
	//! 円周率
	const static float PI = 3.141592654f; 

	//! プレイヤーや敵のステータス管理の構造体
	struct Status {
		int _x = 0;
		int _y = 0;
		int _y_speed = 0;
		int _x_speed = 0;
		bool isDamage = false;
		bool isDamaging = false;
		bool isDead = false;
		bool directRight = true;
	};
	
	//! ステージのブロックのサイズ
	unsigned static char blockWidth = 30;
	unsigned static char blockHeight = 30;

	//! ステージのブロックの数
	static unsigned char blockXNum = 80;
	static unsigned char blockYNum = 40;

	//! ステージのブロック一つ一つのステータス
	struct BlockCell {
		enum class cellStatus {
			none, block,
		};
		int x1, y1, x2, y2;
		cellStatus _status;
	};

	//! スクロール画面の端っこの座標
	static int scrollVerticeLeft = 200;
	static int scrollVerticeRight = 450;

	static int scrollHorizonHead = 200;
	static int scrollHorizonBottom = 450;

	//! プレイヤーオブジェクトや敵オブジェクトの基本行動の分類。
	enum class characterAction {
		Brake, Crouch, Death, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Fall, Run, Walk
		, Hundgun_init, Hundgun_end, Hundgun_horizonal
		, Soard1_init, Soard1_end, Soard2_init, Soard3_init
		, _end
	};

	//! 座標を取り扱う時の次元の定義
	struct Dimention {
		int x = 0;
		int y = 0;
	};

	static unsigned char Accel_gravity = 1;

};