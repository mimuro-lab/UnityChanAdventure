#include "DxLib.h"

/*!
@brief プロジェクトのメイン関数
@date 2020/04/14/11:03
@author mimuro
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	DxLib_Init();	// DXライブラリ初期化処理
	WaitKey();	// キー入力待ち
	DxLib_End();	// DXライブラリ終了処理
	return 0;
}