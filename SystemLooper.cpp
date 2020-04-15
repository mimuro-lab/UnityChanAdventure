#include "SystemLooper.h"


SystemLooper::SystemLooper()//コンストラクタでshared_from_this()を使用できない、コンストラクタ呼び出し時には完全にオブジェクトを生成できていない
{}

bool SystemLooper::Initialize() //constをつけてはならない、privateなメンバ変数を変更するから
{
	scene.push(make_shared<Menu>(shared_from_this()));
	return true;
}

/*!
@brief SystemLooperクラスのエラー処理
@date 2020/04/15/15:27
@author mimuro
*/
bool SystemLooper::Error() const
{
	return false;
}

/*!
@brief 表画面・裏画面処理、メッセージ処理などを行う関数。
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
@brief ループの中心の処理を実行。sceneのtop処理。
@date 2020/04/15/17:31
@author mimuro
*/
void SystemLooper::loop() const
{
	scene.top()->update();
	scene.top()->draw();
}

void SystemLooper::changeScene(eScene Next) const
{

}