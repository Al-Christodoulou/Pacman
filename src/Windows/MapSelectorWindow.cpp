#include "MapSelectorWindow.h"
#include "../PacMan.h"

void MapSelectorWindow::render() 
{
	gPacMan.fillscreen(L' ');
	m_mapMenuList.render();
}

void MapSelectorWindow::runLogic()
{
	m_mapMenuList.handleInput();
}

MapSelectorWindow::MapSelectorWindow()
	: Window(WindowType::Other)
{}