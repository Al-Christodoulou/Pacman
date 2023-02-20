#include "MainMenuList.h"
#include "../PacMan.h"
#include <Windows.h>

void MainMenuList::handleInput()
{
	if (GetAsyncKeyState(L'W') & 0x1)
		goUp();
	else if (GetAsyncKeyState(L'S') & 0x1)
		goDown();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_buttons[getIndex()].onPress();
}

void MainMenuList::render()
{
	// the row from where the menu list starts being drawn from
	constexpr unsigned int baseLine{ 16 };
	// the number of rows distance between the two menu buttons
	constexpr unsigned int lineButtonDelta{ 5 };
	constexpr unsigned int halfWidth{ gScreenWidth / 2 };

	// a lambda for recycling some calculations (perhaps overkill)
	auto calcOffset{ [halfWidth](unsigned int txtWidth) {
		return halfWidth - txtWidth / 2;
	} };

	// render the two buttons
	gPacMan.sendMultiData<textHeight, startBtnWidth>
		(startButton, baseLine, calcOffset(startBtnWidth));
	gPacMan.sendMultiData<textHeight, exitBtnWidth>
		(exitButton, baseLine + lineButtonDelta, calcOffset(exitBtnWidth));

	renderCursor(baseLine, lineButtonDelta);
}

void MainMenuList::renderCursor(unsigned int baseLine, unsigned int lineButtonDelta)
{
	constexpr unsigned int halfWidth{ gScreenWidth / 2 };

	unsigned int lineIndex{ baseLine + getIndex() * lineButtonDelta };
	// the width of the currently selected menu
	unsigned int selectedMenuWidth{ getIndex() == 0 ? startBtnWidth : exitBtnWidth };

	// this is used to place the cursor just some chars before the menu text
	constexpr unsigned int cursorAndMenuDistance{ 4 };

	gPacMan.sendMultiData<textHeight, textHeight>
		(cursor, lineIndex, halfWidth - selectedMenuWidth / 2 - cursorAndMenuDistance);
}

MainMenuList::MainMenuList(const MenuButtonArray_t<2>& menuArray)
	: ConstMenuList{ menuArray }
{}