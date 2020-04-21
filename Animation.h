
/*!
@file Animation.h
@brief ImageDrawクラスが定義されているヘッダファイル
@date 2020/04/21/9:28
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "Define.h"

/*!
@class Animation
@brief 画像をコマ送り表示させたい時に使用するクラス。imagePathにある画像ハンドルのvectorを渡すとアニメーションの管理が行える。
@date 2020/04/18/23:13
@author mimuro
*/
class Animation
{
	//! アニメーションさせたい画像群の画像ハンドルを格納する変数。
	std::vector<int> imageHandles;
	//! update(x, y)を呼び出した時点の画像インデックス。０から始まる。
	char NowDraiwngImageIndex = 0;
	//! update(x, y)を呼び出した時点の画像ハンドル。
	int NowDrawingImageHandle = 0;
	//! アニメーションを途中で終了した時に終わりのインデックスをこれに設定する。設定したインデックスは表示されない。２とした場合、０・１番目のみ表示。
	char DrawingIndexEnd = 99;
	//! 一つの画像を表示させるステップ数。例）６に設定すると１秒間に１０枚の画像が切り替わる。
	char DrawingSteps;
	//! DrawingStepsを数えるためのカウンター。
	char DrawingSteps_counter = 0;
	//! アニメーションが終わったかどうか。
	bool IsEnd = false;
	//! アニメーションさせる為のステータス。
	Define::Status status;
public:

	/*!
	@brief アニメーションさせたい画像群と初期座標は必ず受け取る。それ以外は任意。
	@date 2020/04/21/9:51
	@author mimuro
	*/
	Animation(std::vector<int> _imageHandles, Define::Status _status , char _DrawingSteps = 6, char IndexEnd = 99) :
		imageHandles(_imageHandles)
		, NowDrawingImageHandle(_imageHandles[0])
		, status(_status)
		, DrawingIndexEnd(IndexEnd)
		, DrawingSteps(_DrawingSteps)
	{};
	~Animation() = default;

	//! 更新処理を担う関数。
	void update(Define::Status _status);
	//! 表示処理を担う関数。
	void draw() const;
	//! アニメーションが終わったかどうかを取得する。trueなら終了した。
	const bool isEnd() const { return IsEnd; };

};

