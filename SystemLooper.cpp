
/*!
@file SystemLooper.cpp
@brief SystemLooperクラスのメンバ類の定義を行うCPPファイル
@date 2020/04/15/15:27
@author mimuro
*/

#include "SystemLooper.h"

/*!
@brief ※コンストラクタでshared_from_this()を使用できない、コンストラクタ呼び出し時には完全にオブジェクトを生成できていない。よって変数scene.push()を実行できない。
@date 2020/04/16/3:14
@author mimuro
*/
SystemLooper::SystemLooper()
{}

/*!
@brief SystemOwnerクラス内でオブジェクト生成後一回のみ呼び出される関数。
@brief privateなメンバ変数を変更するからconstをつけてはならない。（scene.push()の使用）
@date 2020/04/16/3:31
@author mimuro
*/
bool SystemLooper::Initialize()
{
	scene.push(make_shared<StartScene>(shared_from_this()));
	return true;
}

/*!
@brief SystemOwnerクラスのメインのwhile分の引数で実行される関数。問題発生時にtrueを返し、問題が無ければfalseを返す。
@date 2020/04/15/15:27
@author mimuro
*/
bool SystemLooper::Error() const
{
	return false;
}

/*!
@brief 表画面・裏画面処理や画面クリア、メッセージ処理などを行う。
@date 2020/04/15/15:27
@author mimuro
*/
bool SystemLooper::scrProcess() const
{
	if (ScreenFlip() != 0)
		return false;
	if (ProcessMessage() != 0)
		return false;
	if (ClearDrawScreen() != 0)
		return false;

	return true;
}

/*!
@brief ループの中心の処理を実行。stock型であるsceneの常にtopの要素の処理を行わせる。
@date 2020/04/15/17:31
@author mimuro
*/
void SystemLooper::loop()
{
	Controller::getIns()->update();
	_fps.wait();
	_fps.draw();
	scene.top()->update();
	scene.top()->draw();
}


/*!
@brief SystemLooperクラスではシーンをメンバ変数sceneで管理するが、そのシーンの変更はこの関数で行う。
@brief この関数はISceneChangerインターフェースクラスに記載されている関数であり、各シーンクラスから呼び出される。
@date 2020/04/16/14:29
@author mimuro
*/
void SystemLooper::changeScene(eScene Next, const bool stackPop)
{
	
	if (stackPop) 
		scene.pop();

	switch (Next) {
	case eStartScene:
		scene.push(make_shared<StartScene>(shared_from_this()));
		break;
	case eMenuScene:
		scene.push(make_shared<MenuScene>(shared_from_this()));
		break;
	case eConfigScene:
		scene.push(make_shared<ConfigScene>(shared_from_this()));
		break;
	case eGameScene:
		scene.push(make_shared<GameScene>(shared_from_this()));
		break;
	default:
		break;
	}
	
}