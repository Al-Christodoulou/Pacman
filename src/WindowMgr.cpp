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