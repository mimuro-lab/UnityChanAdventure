
/*!
@file SystemOwner.cpp
@brief SystemOwnerクラスのメンバ類の定義を行うCPPファイル
@date 2020/04/16/3:41
@author mimuro
*/

#include "SystemOwner.h"

/*!
@brief DxLib上の初期処理を行う。主にウィンドウや描画に関する処理である。
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::initialize() const
{
	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(TRUE);		//ウィンドウサイズを自由に変更できるようにする
	SetOutApplicationLogValidFlag(FALSE);		//ログ出力しない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//フルスクリーン時に縦横比を維持する
	SetWindowText("NewGame");				//ウィンドウタイトルを付ける
	ChangeWindowMode(TRUE);						//ウィンドウモードに変更
//	SetWindowSizeExtendRate(1.0);				//ウィンドウサイズを変更したい時はここに倍率を指定する
	const int COLOR_BIT = 32;					//色のbit数。通常32で良いが軽くするなら16にする
	SetGraphMode(Define::WIN_W, Define::WIN_H, COLOR_BIT);		//ゲーム画面の解像度を設定する
	if (DxLib_Init()) {							//DXライブラリ初期化処理
		return false;							//異常終了したら即座にやめる
	}
	SetDrawScreen(DX_SCREEN_BACK);				//裏画面処理を設定する
	return true;
}

/*!
@brief DxLibの終了処理を行う。
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::finalize() const
{
	DxLib_End();
	return true;
}

/*!
@brief SystemLooperクラスのオブジェクトを生成し、処理を管理する。
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::main() const
{
	
	shared_ptr<SystemLooper> looper = make_shared<SystemLooper>();

	if (!looper->Initialize())
		return false;

	while (!looper->Error()) {
		if (!looper->scrProcess())
			break;
		looper->loop();
	}

	return true;
}