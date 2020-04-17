
/*!
@file ISceneChanger.h
@brief ISceneChangerクラスが定義されているヘッダファイル。
@date 2020/04/16/2:50
*/

#pragma once
#include "Define.h"
/*!
@class ISceneChanger
@brief SystemLooperクラスが持つchangeSceneメンバ関数を外部クラスで使用する為のインターフェース。
@date 2020/04/16/2:50
*/
class ISceneChanger {
public:
	ISceneChanger() = default;
	~ISceneChanger() = default;
	//! このクラスを継承したクラスは必ずこの関数を定義しなければならないように約束する。
	virtual void changeScene(eScene Next, const bool stackPop) = 0;
};