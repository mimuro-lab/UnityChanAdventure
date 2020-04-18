#include "SelectWindow.h"

const bool SelectWindow::updateSelectWindow()
{

	if (Controller::getIns()->getSelect()) {
		_IsSelected = !_IsSelected;
	}

	if (_IsSelected) {
		if (Controller::getIns()->getRight())
			isReturn = false;
		if (Controller::getIns()->getLeft())
			isReturn = true;

		if (Controller::getIns()->getPush_A()) {
			if (isReturn)
				changerInSelectWindow->changeScene(eNone, true);
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
	DrawFormatString(100, 100, GetColor(255, 255, 255), "SelectWindow\n return to a previous scene?");

	unsigned int yesColor, noColor;
	yesColor = noColor = GetColor(255, 255, 255);

	if (isReturn)
		yesColor = GetColor(255, 0, 0);
	else
		noColor = GetColor(255, 0, 0);

	DrawFormatString(120, 150, yesColor, "yes");
	DrawFormatString(170, 150, noColor, "no");

}

void SelectWindow::ValidSelectWindow() 
{
	updateSelectWindow();
	drawSelectWindw();
}