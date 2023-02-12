#include "MainMenuList.h"
#include "PacMan.h"
#include <Windows.h>

void MainMenuList::handleInput()
{
	if (GetAsyncKeyState(L'W') & 0x1)
		goUp();
	else if (GetAsyncKeyState(L'S') & 0x1)
		goDown();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_buttons[m_selectedIndex].onPress();
}

void MainMenuList::render()
{
	constexpr wchar_t startButton[3][23]{
		L"/-- ---   ^   /--/ ---",
		L"\\-\\  |   /-\\  |-/   | ",
		L"--/  |  /   \\ |  \\  | "
	};

	constexpr wchar_t exitButton[3][17]{
		L"\/--  \\\/  --- ---",
		L"|--  \/\\   |   | ",
		L"\\-- \/  \\ ---  | "
	};

	for (unsigned int i{ 0 }; i < 3; i++)
	{
		gPacMan.sendData(startButton[i], 23U, gScreenWidth * (16 + i) + gScreenWidth / 2 - 23 / 2);
		gPacMan.sendData(exitButton[i], 17U, gScreenWidth * (21 + i) + gScreenWidth / 2 - 17 / 2);
	}

	// TODO: organize this better
	unsigned int lineIndex{ gScreenWidth * (16 + m_selectedIndex * 5) };
	gPacMan.sendData(L'\\', lineIndex + gScreenWidth / 2 - 16);
	gPacMan.sendData(L'>', lineIndex + gScreenWidth + gScreenWidth / 2 - 15);
	gPacMan.sendData(L'/', lineIndex + gScreenWidth * 2 + gScreenWidth / 2 - 16);
}

MainMenuList::MainMenuList(std::initializer_list<MenuButton> buttons)
	: MenuList{ buttons }
{}