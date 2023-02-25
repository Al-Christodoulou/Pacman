#include "WindowMgr.h"
#include "Windows/GameWindow.h"
#include "Windows/MainMenuWindow.h"
#include "Windows/MapSelectorWindow.h"

// yet another forward declaration
class MapFile;

void WindowMgr::update()
{
	// first make sure to pop any windows that are
	// marked for termination
	while (m_windowStack.back().get()->doTerminate())
	//while (m_windowStack.top().get().doTerminate())
		m_windowStack.pop_back();

	// all the windows will get rendered, from bottom to top
	for (size_t i{ 0 }; i < m_windowStack.size(); i++)
	{
		m_windowStack[i].get()->render();
	}
	// but only the last one will have its logic run
	m_windowStack.back().get()->runLogic();
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