#pragma once

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