#include "SelectWindow.h"

const bool SelectWindow::updateSelectWindow()
{

	if (Controller::getIns()->getSelect()) {
		_IsSelected = !_IsSelected;
	}

	if (_IsSelected) {
		if (Controller::getIns()->getRight() || Controller::getIns()->getLeft())
			isReturn = !isReturn;

		if (Controller::getIns()->getPush_A()) {
			if (isReturn)
				changerInSelectWindow->changeScene(eStartScene, false);
			else
			{
				isReturn = false;
				_IsSelected = false;
			}
		}
	}

	return true;
}

void SelectWindow::drawSelectWindw() const
{
	if (!_IsSelected)
		return;
	DrawFormatString(100, 100, GetColor(255, 255, 255), "SelectWindow");

	unsigned int yesColor, noColor;
	yesColor = noColor = GetColor(255, 255, 255);

	if (isReturn)
		yesColor = GetColor(255, 0, 0);
	else
		noColor = GetColor(255, 0, 0);

	DrawFormatString(70 + 30, 120, yesColor, "yes");
	DrawFormatString(120 + 30, 120, noColor, "no");

}

void SelectWindow::ValidSelectWindow() 
{
	updateSelectWindow();
	drawSelectWindw();
}