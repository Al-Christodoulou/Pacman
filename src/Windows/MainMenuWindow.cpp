#include "MainMenuWindow.h"
#include "../PacMan.h"
#include "../Engine/Random.h"
#include "../Windows/MapSelectorWindow.h"

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
	renderList();
}

void MainMenuWindow::renderList()
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

	renderListCursor(baseLine, lineButtonDelta);
}

void MainMenuWindow::renderListCursor(unsigned int baseLine, unsigned int lineButtonDelta)
{
	constexpr unsigned int halfWidth{ gScreenWidth / 2 };

	const unsigned int lineIndex{ baseLine + m_menuIndex * lineButtonDelta };
	// the width of the currently selected menu
	const unsigned int selectedMenuWidth{ m_menuIndex == 0 ? startBtnWidth : exitBtnWidth };

	// this is used to place the cursor just some chars before the menu text
	constexpr unsigned int cursorAndMenuDistance{ 4 };

	gPacMan.sendMultiData<textHeight, textHeight>
		(leftCursor, lineIndex, halfWidth - selectedMenuWidth / 2 - cursorAndMenuDistance);
	gPacMan.sendMultiData<textHeight, textHeight>
		(rightCursor, lineIndex, halfWidth + selectedMenuWidth / 2 + 1);
}

void MainMenuWindow::runLogic()
{
	if (gPacMan.isKeyTapped(L'W'))
		++m_menuIndex;
	else if (gPacMan.isKeyTapped(L'S'))
		--m_menuIndex;

	if (gPacMan.isKeyTapped(VK_RETURN))
	{
		switch (m_menuIndex)
		{
		case 0: // start
			gPacMan.getWindowMgr().pushAnyWindow<MapSelectorWindow>();
			break;
		case 1: // exit
			break;
		}
		m_state_terminate = true;
	}
}

MainMenuWindow::MainMenuWindow()
	: Window(WindowType::Other)
{}
