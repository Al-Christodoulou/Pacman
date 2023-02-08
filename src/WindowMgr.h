#pragma once
#include "Engine/Window.h"
#include "WindowTypes.h"
#include <vector>
#include <memory>

using PacmanWindow = Window<WindowType>;
using WindowStack_t = std::vector<std::unique_ptr<PacmanWindow>>;
class EntityMgr; // forward declare the class to avoid includes

class WindowMgr
{
private:
	WindowStack_t m_windowStack{};

public:
	void update();

	void pushGameWindow();
	void pushMainMenuWindow();

	// quite ugly. in order for a Character to search the entity
	// array, the sequence of access is:
	// gPacMan->WindowMgr->GameWindow->EntityMgr
	// so you need a getter for WindowMgr by PacMan, which is
	// useful to have anyway, but you also need one for GameWindow
	// by WindowMgr, which "pollutes" the class with more methods
	// just for one unique behavior of a Window. it's okay for now
	const EntityMgr* const tryGetEntMgr() const;
};