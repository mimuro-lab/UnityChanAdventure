#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
#include <memory>

using namespace std;

class Menu : public AbstractScene
{
public:
	Menu(
		shared_ptr<ISceneChanger> _changer
	) 
		: AbstractScene(_changer) {};
	~Menu() = default;

	void draw()  override;
	void update() override;
};

