
/*!
@file Animation.h
@brief Animationクラスが定義されているヘッダファイル
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
	unsigned char NowDraiwngImageIndex = 0;
	//! update(x, y)を呼び出した時点の画像ハンドル。
	int NowDrawingImageHandle = 0;
	//! アニメーションを途中で終了した時に終わりのインデックスをこれに設定する。設定したインデックスは表示されない。２とした場合、０・１番目のみ表示。
	char DrawingIndexEnd = 99;
	//! 一つの画像を表示させるステップ数。例）１２に設定すると１秒間に５枚の画像が切り替わる。（６０fpsで、１２ステップで１枚更新）
	char DrawingSteps;
	//! DrawingStepsを数えるためのカウンター。
	char DrawingSteps_counter = 0;
	//! アニメーションを描画するとき、水平方向にずらす座標量。
	char DrawingShiftX = 0;
	//! アニメーションを描画するとき、垂直方向にずらす座標量。
	char DrawingShiftY = 0;
	//! アニメーションが終わったかどうか。
	bool IsEnd = false;
	//! アニメーション終了時に画像を表示し続けるか？
	bool IsEndDrawing = false;
	//! アニメーションさせる為のステータス。
	Define::Status status;
	//! 画像の拡大・縮小の倍率
	double scaleRate = 1.0;

	double rotation = 0;

public:

	/*!
	@brief アニメーションさせたい画像群と初期座標は必ず受け取る。それ以外は任意。
	@date 2020/04/21/9:51
	@author mimuro
	*/
	Animation(std::vector<int> _imageHandles, Define::Status _status , char _DrwaingShiftX = 0, char _DrawingShiftY = 0
		, char _DrawingSteps = 6, char IndexEnd = 99, bool _IsEndDrawing = true, double _scaleRate = 1.0) :
		imageHandles(_imageHandles)
		, NowDrawingImageHandle(_imageHandles[0])
		, status(_status)
		, DrawingShiftX(_DrwaingShiftX)
		, DrawingShiftY(_DrawingShiftY)
		, DrawingIndexEnd(IndexEnd)
		, DrawingSteps(_DrawingSteps)
		, IsEndDrawing(_IsEndDrawing)
		, scaleRate(_scaleRate)
	{};
	~Animation() = default;

	//! 更新処理を担う関数。
	void update(Define::Status _status);
	//! 表示処理を担う関数。
	void draw() const;
	//! アニメーションが終わったかどうかを取得する。trueなら終了した。
	const bool isEnd() const { return IsEnd; };
	//! アニメーションを元に戻す関数。
	void refreshing();

	//! ある画像における、同じ画像を一定時間表示するために数えるカウンター
	const char getDrawingStepsCounter() { return DrawingSteps_counter; }
	//! アニメーションにおける、表示する画像の番号
	const char getNowDrawingImageIndex() { return NowDraiwngImageIndex; }
	//! 画像の枚数
	const int getImagesSize() { return imageHandles.size(); }

	void arrangeScale(double rate) {
		scaleRate = rate;
	};

	double getScale() {
		return scaleRate;
	}

	//!　ラジアンではなく、360度表示で入力
	void arrangeRotation(double rota) {
		rotation = rota;
	}

};

