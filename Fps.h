
/*!
@file Fps.h
@brief Fpsクラスが定義されているヘッダファイル
@date 2020/04/18/23:02
@author mimuro
*/

#pragma once
#include <list>

/*!
@class Fps
@brief SystemLooperクラスの一回当たりの処理の時間を一定にするFps制御を担うクラス。
@date 2020/04/18/23:03
@author mimuro
*/
class Fps {

public:
    Fps();
    void wait();
    void draw() const;

private:
    std::list<int> _list;
    float    _fps;
    unsigned _counter;

    void        updateAverage();
    void        regist();
    unsigned    getWaitTime() const;

};