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
	//!ウィンドウサイズ横
	const static int WIN_W;

	//!ウィンドウサイズ縦
	const static int WIN_H;
	
	//!円周率
	const static float PI;	
};