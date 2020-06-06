#pragma once

#include "Singleton.h"
#include <vector>
#include <DxLib.h>

using namespace std;

class ImagePath_Effect :
	public Singleton<ImagePath_Effect>
{
	ImagePath_Effect() = default;
	friend Singleton< ImagePath_Effect >;
public:

	//! characterActionAction‚Ì‰æ‘œ‚Ö‚ÌƒpƒX‚ğ‚Ü‚Æ‚ß‚½•Ï”B
	//const vector<int> bulletNormal;
	//int bulletNormal[25];
	//LoadDivGraph("images/Effect/pipo-mapeffect011.png", 20, 5, 5, 120, 120, bulletNormal);
	//LoadDivGraph("images/Effect/pipo-mapeffect011.png", 20, 5, 4, 120, 120, bulletNormal);

};