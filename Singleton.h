
/*!
@file Singleton.h
@brief Singletonクラスが定義されているヘッダファイル
@date 2020/04/16/20:06
@author mimuro
*/

#pragma once

template <typename _T>

/*!
@class Singleton
@brief オブジェクトが一つしかない事を約束するシングルトンクラス。public Singleton<class _T>と継承すると継承元クラスがシングルトンになる。
@date 2020/04/16/20:08
@author mimuro
*/
class Singleton {
protected:
	Singleton() = default;
	virtual ~Singleton() = default;
	Singleton(const Singleton& r) = default;
	Singleton& operator=(const Singleton& r) = default;

public:
	static _T* getIns() {
		static _T inst;
		return &inst;
	}
};