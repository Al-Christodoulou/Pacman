#include "MainMenuList.h"
#include <Windows.h>

void MainMenuList::handleInput()
{
	if (GetAsyncKeyState(L'W') & 0x8000)
		goUp();
	else if (GetAsyncKeyState(L'S') & 0x8000)
		goDown();
}

MainMenuList::MainMenuList(std::initializer_list<MenuButton> buttons)
	: MenuList{ buttons }
{}