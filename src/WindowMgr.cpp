#include "WindowMgr.h"
#include "Windows/GameWindow.h"
#include "Windows/MainMenuWindow.h"
#include "Windows/MapSelectorWindow.h"

// yet another forward declaration
class MapFile;

bool WindowMgr::update()
{
	// first make sure to pop any windows that are
	// marked for termination
	while (m_windowStack.back()->doTerminate())
	{
		m_windowStack.pop_back();
		if (m_windowStack.empty())
			return false;
	}

	// all the windows will get rendered, from bottom to top
	for (size_t i{ 0 }; i < m_windowStack.size(); i++)
	{
		m_windowStack[i]->render();
	}
	// but only the last one will have its logic run
	m_windowStack.back()->runLogic();
	return true;
}

const EntityMgr* const WindowMgr::tryGetEntMgr() const
{
	if (m_windowStack.empty())
		return nullptr;

	const PacmanWindow* topWindow{ m_windowStack.back().get() };
	return topWindow->getWindowType() == WindowType::GameWindow ?
		&static_cast<const GameWindow*>(topWindow)->getEntMgr() :
		nullptr;
}