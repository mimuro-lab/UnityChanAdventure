
/*!
@file AbstractScene.h
@brief AbstractSceneクラスが定義されているヘッダファイル。
@date 2020/04/16/2:40
@author mimuro
*/

#pragma once
#include "ISceneChanger.h"
#include <memory>

using namespace std;

/*!
@class AbstractScene
@brief シーンを管理するクラス、SystemLooperで使用。各シーンクラスはこのクラスを継承する。
@date 2020/04/14/16:00
@author mimuro
*/
class AbstractScene
{
	int unsigned counter_form_start = 0;
protected:
	//! 全てのシーンクラスでIScneChanger型のオブジェクトを持たせる。SystemLooperクラスのchangeSceneメンバ関数を呼び出すため。いわゆるコールバックというやつ。
	shared_ptr<ISceneChanger> changer;

	//! 継承先の始まりからのコマ数をカウントする。
	void counterUpdate() { counter_form_start++; };

	//! カウンターの値を獲得する。
	const int getCounter() { return counter_form_start; };

public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、changerに代入する。
	AbstractScene(shared_ptr<ISceneChanger> _changer): changer(_changer){};

	~AbstractScene() = default;

	//! 継承先のシーンクラスでは必ずupdate()関数を作る事を約束する。
	virtual void update() = 0;

	//! 継承先のシーンクラスでは必ずdraw()関数を作る事を約束する。
	virtual void draw() = 0;
};

