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

void WindowMgr::pushGameWindow(const MapFile& mapFile)
{
	//GameWindow gameWin{};
	//m_windowStack.push_back(std::ref(static_cast<Window&>(gameWin)));
	m_windowStack.push_back(std::make_unique<GameWindow>(mapFile));
}

void WindowMgr::pushMainMenuWindow()
{
	auto uniquePtr{ std::make_unique<MainMenuWindow>() };
	std::unique_ptr<PacmanWindow> newPtr{ static_cast<PacmanWindow*>(uniquePtr.release()) };

	m_windowStack.push_back(std::move(newPtr));
}

void WindowMgr::pushMapSelectorWindow()
{
	auto uniquePtr{ std::make_unique<MapSelectorWindow>() };
	std::unique_ptr<PacmanWindow> newPtr{ static_cast<PacmanWindow*>(uniquePtr.release()) };

	m_windowStack.push_back(std::move(newPtr));
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