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
	constexpr wchar_t startButton[3][23]{
		L"/-- ---   ^   /--/ ---",
		L"\\-\\  |   /-\\  |-/   | ",
		L"--/  |  /   \\ |  \\  | "
	};

	constexpr wchar_t exitButton[3][17]{
		L"/--  \\/  --- ---",
		L"|--  /\\   |   | ",
		L"\\-- /  \\ ---  | "
	};

	// the line from where the menu list starts being drawn from
	constexpr unsigned int baseLine{ 16 };
	// the number of lines distance between the two menu buttons
	constexpr unsigned int lineButtonDelta{ 5 };
	constexpr unsigned int halfWidth{ gScreenWidth / 2 };

	gPacMan.sendMultiData<3, 23>(startButton, baseLine, halfWidth - 23 / 2);
	gPacMan.sendMultiData<3, 17>(exitButton, baseLine + lineButtonDelta, halfWidth - 17 / 2);

	unsigned int lineIndex{ baseLine + getIndex() * lineButtonDelta };
	// the row of the currently selected menu, this is used to place the cursor just some chars before it
	unsigned int selectedMenuRow{};
	switch (getIndex())
	{
	case 0:
		selectedMenuRow = 23;
		break;
	case 1:
		selectedMenuRow = 17;
		break;
	}

	constexpr unsigned int cursorAndMenuDistance{ 4 };
	constexpr wchar_t cursor[3][3]{
		L"\\",
		L" >",
		L"/"
	};
	gPacMan.sendMultiData<3, 3>(cursor, lineIndex, halfWidth - selectedMenuRow / 2 - cursorAndMenuDistance);
}

MainMenuList::MainMenuList(const MenuButtonArray_t<2>& menuArray)
	: ConstMenuList{ menuArray }
{}