
/*!
@file Task.h
@brief Taskクラスが定義されているヘッダファイル。
@date 2020/04/21/12:46
*/

#pragma once

/*!
@class Task
@brief updateとdraw関数を必ず持つ様に設定するインターフェースクラス。
@date 2020/04/21/12:46
*/
class Task {
public:
    virtual ~Task() {}
    //! 初期化処理は実装してもしなくてもいい
    virtual void initialize() {}     
    //! 終了処理は実装してもしなくてもいい
    virtual void finalize() {}     
    //! 更新処理は必ず継承先で実装する
    virtual void update() = 0;   
    //! 描画処理は必ず継承先で実装する
    virtual void draw() = 0;   
};