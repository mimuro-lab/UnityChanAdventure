#pragma onces
#include "ISceneChanger.h"
#include <memory>

using namespace std;

/*!
@brief シーンを管理するクラス、SystemLooperで使用
@date 2020/04/14/16:00
@author mimuro
*/

class AbstractScene
{
	shared_ptr<ISceneChanger> changer = make_shared<ISceneChanger>();
public:
	AbstractScene() = default;
	~AbstractScene() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
};

