#pragma once
#include "Engine/Window.h"
#include "Engine/UniquePtrUtils.h"
#include "WindowTypes.h"
#include <list>
#include <memory>

using PacmanWindow = Window<WindowType>;
using WindowStack_t = std::list<std::unique_ptr<PacmanWindow>>;
class EntityMgr; // forward declare the class to avoid includes
class MapFile;

class WindowMgr
{
private:
	WindowStack_t m_windowStack{};

public:
	// returns false if there's nothing to update (no windows)
	bool update();

	template <typename WinType, typename... Args>
	void pushAnyWindow(Args... args)
	{
		auto uniquePtr{ std::make_unique<WinType>(args...) };
		m_windowStack.push_back(
			std::move(
				util::upcast<PacmanWindow, WinType>(std::move(uniquePtr))
			)
		);
	}

	const PacmanWindow* getTopWindow() const;

	// quite ugly. in order for a Character to search the entity
	// array, the sequence of access is:
	// gPacMan->WindowMgr->GameWindow->EntityMgr
	// so you need a getter for WindowMgr by PacMan, which is
	// useful to have anyway, but you also need one for GameWindow
	// by WindowMgr, which "pollutes" the class with more methods
	// just for one unique behavior of a Window. it's okay for now
	EntityMgr* const tryGetEntMgr();
};