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
	gPacMan.sendMultiData<height, width>(titleText, 3, gScreenWidth / 2 - width / 2);
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

	return MenuButtonArray_t<2>{ MenuButton{ startButtonPress }, MenuButton{ endButtonPress } };
}

MainMenuWindow::MainMenuWindow()
	: Window(WindowType::Other), m_mainMenuList{ constructMainMenuList() }
{}
