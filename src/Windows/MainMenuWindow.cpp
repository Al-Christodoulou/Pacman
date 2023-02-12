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

	m_mainMenuList.render();
}

void MainMenuWindow::runLogic()
{
	m_mainMenuList.handleInput();
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