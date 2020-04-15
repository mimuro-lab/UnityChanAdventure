
/*!
@file main.cpp
@brief プロジェクトのメイン関数が定義されているCPPファイル
@date 2020/04/14/11:03
@author mimuro
*/

#include <DxLib.h>
#include "SystemOwner.h"
#include <memory>
using namespace std;

//!@brief プロジェクトのメイン関数。SystemOwnerクラスのオブジェクトを一つだけ定義し、それを操作する。 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	shared_ptr<SystemOwner> owner = make_shared<SystemOwner>();

	if (owner->initialize()) {
		owner->main();
	}

	owner->finalize();

	return 0;
}
