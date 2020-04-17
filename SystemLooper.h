
/*!
@file SystemLooper.h
@brief SystemLooperクラスが定義されているヘッダファイル
@date 2020/04/15/15:12
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <stack>
#include <memory>
#include "Controller.h"
#include "Fps.h"
#include "ISceneChanger.h"
#include "AbstractScene.h"
#include "StartScene.h"
#include "MenuScene.h"
#include "ConfigScene.h"
#include "GameScene.h"

using namespace std;

/*!
@class SystemLooper
@brief ループする処理の中心を担うクラス
@date 2020/04/15/15:12
@author mimuro
*/
class SystemLooper : public ISceneChanger,
	public enable_shared_from_this<SystemLooper>
{	
	//! シーンを管理する変数。各要素がshred_ptr<AbstractScene>型のstack型を使用する。
	stack <shared_ptr<AbstractScene>> scene;

	//! FPS処理を施すためのオブジェクト。
	Fps _fps;
public:
	//! 初期化処理を行う関数。
	SystemLooper();
	~SystemLooper() = default;

	//! 初期化処理を行う関数。
	bool Initialize();

	//! エラー処理を行う関数。
	bool Error() const;

	//! 画面処理を行う関数。
	bool scrProcess() const;

	//! メインの繰り返し処理を行う関数。
	void loop();

	//! シーン替えを行う関数。
	void changeScene(eScene NextScene, const bool stackClear) override;
};

