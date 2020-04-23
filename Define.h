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
enum eScene {
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
class Define final {
public:
	//! ウィンドウサイズ横
	const static int WIN_W;

	//! ウィンドウサイズ縦
	const static int WIN_H;
	
	//! 円周率
	const static float PI;	

	//! プレイヤーや敵のステータス管理の構造体
	struct Status {
		int _x = 0;
		int _y = 0;
		bool directRight = true;
	};
	
	//! ステージのブロック一つ一つのステータス
	struct BlockCell {
		enum cellStatus {
			none, block,
		};
		int x1, y1, x2, y2;
		cellStatus _status;
	};

	//! プレイヤーオブジェクトや敵オブジェクトの基本行動の分類。
	enum class rollAction_Basic {
		Brake, Crouch, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Fall, Run, Walk, _end
	};

};