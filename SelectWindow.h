
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
	//! ひとつ前のコマのセレクトウィンドウの状態。ウィンドウの立下りを検知するための変数。
	bool _preIsSelected = false;

	//! シーン変更のためのコールバック。SystemLooperのchangeScene関数を用いるために定義。
	std::shared_ptr<ISceneChanger> changerInSelectWindow;

	//! セレクトボタンが押されたかを保持する。以前の状態を保持する変数（イメージはフリップフロップ回路）
	bool _IsSelected = false;

	//! セレクトウィンドウが閉じられた瞬間を察知する。セレクトウィンドウが閉じた瞬間のみコントローラの更新が必要。
	bool _IsClosed = false;

	//! ひとつ前のシーンに戻るかを選択するための変数。
	bool isReturn = false;

	//! セレクトウィンドウを使用する為の前処理の関数。
	const bool updateSelectWindow();

public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	SelectWindow(std::shared_ptr<ISceneChanger> _changer) : changerInSelectWindow(_changer) {};
	~SelectWindow() = default;

	//! セレクトウィンドウを有効にする為の関数。
	void ValidSelectWindow();

	//! セレクトウィンドウを表示する関数。
	void drawSelectWindow() const;

	//! 現在セレクトウィンドウが有効になっているかどうかを確認するための関数。
	bool const IsSelected() const { return _IsSelected; }

	//! セレクトウィンドウの立下りを確認するための関数。
	bool const IsSelectWindow_Closed() const { return _IsClosed; }
};