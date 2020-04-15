#pragma once

/*!
@brief シーンの定義
@date 2020/04/15/16:47
@author mimuro
*/
enum eScene {
	eMenu,
	eConfig,
};

/*!
@brief あらゆるパラメータの定義を保持するクラス
@date 2020/04/15/0:19
@author mimuro
*/
class Define final {
public:
	const static int WIN_W;	//ウィンドウサイズ横
	const static int WIN_H;	//ウィンドウサイズ縦

	const static float PI;	//円周率
};