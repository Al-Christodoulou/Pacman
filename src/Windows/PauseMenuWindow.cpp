#include "../PacMan.h"
#include "../WindowTypes.h"
#include "PauseMenuWindow.h"

void PauseMenuWindow::render()
{
	BorderedWindow::render();

	// render the title
	renderTextCentered(-1, L"Pause Menu", 10);

	// too bad C++ can't have nested functions so we have to use lambdas
	constexpr auto calcOffsetY{ [](const unsigned int i) {
		return 1 + i * 2;
	}};

	for (unsigned int i{ 0 }; i < MenuOptions::max_num_options; i++)
	{
		m_menuOptionsOffsetsX[i] = renderTextCentered(calcOffsetY(i), MenuOptions[i], MenuOptionsLens[i]);
	}
	renderText(m_menuOptionsOffsetsX[m_menuIndex] - 2, calcOffsetY(m_menuIndex), L"> ");
	renderText(m_menuOptionsOffsetsX[m_menuIndex] + MenuOptionsLens[m_menuIndex] + 1, calcOffsetY(m_menuIndex), L"< ");
}

void PauseMenuWindow::runLogic()
{
	if (gPacMan.isKeyTapped(L'W'))
		--m_menuIndex;
	else if (gPacMan.isKeyTapped(L'S'))
		++m_menuIndex;

	if (gPacMan.isKeyTapped(VK_ESCAPE))
		m_state_terminate = true;
	else if (gPacMan.isKeyTapped(VK_RETURN))
	{
		switch (m_menuIndex)
		{
		case MenuOptions::Resume_game:
			m_state_terminate = true;
			break;
		case MenuOptions::Options:
			//gPacMan.getWindowMgr().pushAnyWindow<OptionsWindow>();
			break;
		case MenuOptions::Exit:
			// TODO: figure out a way to make both this window and GameWindow
			// terminate when in this point of execution
			m_state_terminate = true;
			break;
		}
	}
}

PauseMenuWindow::PauseMenuWindow()
	: BorderedWindow{ 18, 8 }
{
	for (unsigned int i{ 0 }; i < MenuOptions::max_num_options; i++)
		m_menuOptionsOffsetsX[i] = 0;
}