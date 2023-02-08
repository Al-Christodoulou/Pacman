#include "MainMenuWindow.h"
#include "../PacMan.h"
#include "../Engine/Random.h"

void MainMenuWindow::render()
{
	constexpr unsigned int width{ 52 };
	constexpr unsigned int height{ 5 };
	constexpr wchar_t titleText[height][width]{
		L"####     #       #### ###    ###     #     ###   ##",
		L"#  #    # #     ##    ## #  # ##    # #    ## #  ##",
		L"####   #####   ##     ##  ##  ##   #####   ##  # ##",
		L"##    #     #   ##    ##      ##  #     #  ##   ###",
		L"##   #       #   #### ##      ## #       # ##    ##"
	};

	gPacMan.fillscreen(L' ');

	// the top left position of the text. gScreenWidth * 3 so it's
	// on the 4th line, gScreenWidth / 2 so it starts in the middle
	constexpr unsigned int baseOffset{ gScreenWidth * 3 + gScreenWidth / 2 - width / 2 };
	for (unsigned int i{ 0 }; i < height; i++)
	{
		gPacMan.sendData(titleText[i], width, baseOffset + gScreenWidth * i);
	}

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
}

void MainMenuWindow::runLogic()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		gPacMan.getWindowMgr().pushGameWindow();
}

MainMenuList MainMenuWindow::constructMainMenuList()
{
	auto startButtonPress{ []() { gPacMan.getWindowMgr().pushGameWindow(); } };
	auto endButtonPress{ []() { /* this has to call an exit somehow */ } };

	return { MenuButton{ startButtonPress }, MenuButton{ endButtonPress } };
}

MainMenuWindow::MainMenuWindow()
	: Window(WindowType::Other), m_mainMenuList{ constructMainMenuList() }
{}