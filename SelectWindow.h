#pragma once

#include "Controller.h"
#include "ISceneChanger.h"
#include <memory>

class SelectWindow
{
	std::shared_ptr<ISceneChanger> changerInSelectWindow;

	bool _IsSelected = false;

	bool isReturn = false;

	const bool updateSelectWindow();
	void drawSelectWindw() const;

public:
	SelectWindow(std::shared_ptr<ISceneChanger> _changer) : changerInSelectWindow(_changer) {};
	~SelectWindow() = default;
	void ValidSelectWindow();
	bool const IsSelected() const { return _IsSelected; };
};