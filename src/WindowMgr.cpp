#include "WindowMgr.h"
#include "Windows/GameWindow.h"
#include "Windows/MainMenuWindow.h"
#include "Windows/MapSelectorWindow.h"

// yet another forward declaration
class MapFile;

bool WindowMgr::update()
{
	if (m_windowStack.empty())
		return false;

	auto iter{ m_windowStack.begin() };
	while (iter != m_windowStack.end())
	{
		if ((*iter)->doTerminate())
			iter = m_windowStack.erase(iter);
		else // all the windows will get rendered, from bottom to top
			(*iter)->render();

		if (iter != m_windowStack.end())
			++iter;
	}
	if (m_windowStack.empty())
		return false;
	m_windowStack.back()->runLogic(); // but only the last one will have its logic run
	return true;
}

EntityMgr* const WindowMgr::tryGetEntMgr()
{
	if (m_windowStack.empty())
		return nullptr;

	return m_windowStack.back()->getWindowType() == WindowType::GameWindow ?
		&static_cast<GameWindow*>(m_windowStack.back().get())->getEntMgr() :
		nullptr;
}

PacmanWindow* WindowMgr::getTopWindow()
{
	return m_windowStack.back().get();
}

// iterate through the window stack, and the first window to be found where
// m_stateTerminate == false, set it to true. effectively:
//
// m_windowStack example:
// (Window1).m_state_terminate = true;
// (Window2).m_state_terminate = true;
// (Window3).m_state_terminate = true;
// (Window4).m_state_terminate = false; => now set to true
// (Window5).m_state_terminate = false;
// ...
// (WindowN).m_state_terminate = X;
//
// this is useful in a scenario where we need to terminate two windows at once
// for example in the pause menu window when the user presses Exit, both it
// and GameWindow need to be terminated at once
void WindowMgr::terminateTopNonTermWindow()
{
	if (m_windowStack.empty())
		return;

	// a reverse iterator, where ++ goes backwards, which is essentialy how a
	// stack would "iterate" through its content
	auto riter{ m_windowStack.rbegin() };
	while (riter != m_windowStack.rend())
	{
		if (!(**riter).m_state_terminate)
		{
			(**riter).m_state_terminate = true;
			break;
		}
		else
			++riter;
	}
}