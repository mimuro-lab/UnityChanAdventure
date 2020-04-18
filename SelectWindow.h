
/*!
@file SelectWindow.h
@brief SelectWindowクラスが定義されているヘッダファイル
@date 2020/04/18/23:12
@author mimuro
*/

#pragma once
#include "Controller.h"
#include "ISceneChanger.h"
#include <memory>

/*!
@class SelectWindow
@brief セレクト画面の処理を担うクラス。セレクト画面を有効にしたいシーンに継承させると使用できる。
@date 2020/04/18/23:13
@author mimuro
*/
class SelectWindow
{
	//! シーン変更のためのコールバック。SystemLooperのchangeScene関数を用いるために定義。
	std::shared_ptr<ISceneChanger> changerInSelectWindow;

	//! セレクトボタンが押されたかを保持する。以前の状態を保持する変数（イメージはフリップフロップ回路）
	bool _IsSelected = false;

	//! ひとつ前のシーンに戻るかを選択するための変数。
	bool isReturn = false;

	//! セレクトウィンドウを使用する為の前処理の関数。
	const bool updateSelectWindow();

	//! セレクトウィンドウを表示する関数。
	void drawSelectWindw() const;

public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	SelectWindow(std::shared_ptr<ISceneChanger> _changer) : changerInSelectWindow(_changer) {};
	~SelectWindow() = default;

	//! セレクトウィンドウを有効にする為の関数。継承先のクラスはこの関数を呼び出すだけでセレクト画面が有効になる。
	void ValidSelectWindow();

	//! 現在セレクトウィンドウが有効になっているかどうかを確認するための関数。
	bool const IsSelected() const { return _IsSelected; };
};