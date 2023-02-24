#include "GameWindow.h"
#include "../PacMan.h"
#include "../Engine/Random.h"
#include "../WanderingLouse.h"
#include "../Ghost.h"
#include "../MapFile.h"

void GameWindow::render()
{
	gPacMan.fillscreen(L' ');
	renderAllEntities();

	gPacMan.swprintf_s(25, L"X: %.3f, Y: %.2f", m_player->getVirtualX(), m_player->getVirtualY());
}

void GameWindow::runLogic()
{
	// make all characters think
	for (std::unique_ptr<Entity>& entPtr : m_entMgr.getEntities())
	{
		Entity* rawEntPtr{ entPtr.get() };
		if (rawEntPtr->getEntType() == EntityType::Character)
			static_cast<Character*>(rawEntPtr)->think();
	}

	/*swprintf_s(m_screen, 40, L"X: %f, Y: %f",
		player->getVirtualX(), player->getVirtualY()
	);
	swprintf_s(m_screen + gScreenWidth, 30, L"DT: %f", m_engine.getDeltaTime());*/

	// if the player presses escape, the GameWindow will terminate and we go back to the
	// main menu
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		m_state_terminate = true;
}

void GameWindow::initEntities(const MapFile& mapFile)
{
	/*m_player = m_entMgr.createPlayer(gScreenWidth / 2, gScreenHeight / 2, 0x555);

	//for (int i{ 0 }; i < 50; i++)
	//	m_entMgr.createEnt(Random::get(0, gScreenWidth), Random::get(0, gScreenHeight), L'#');
	m_entMgr.createEnt((gScreenWidth / 2), (gScreenHeight / 2) - 4, L'#');
	m_entMgr.createEnt((gScreenWidth / 2) - 1, (gScreenHeight / 2) - 4, L'#');
	m_entMgr.createEnt((gScreenWidth / 2) + 1, (gScreenHeight / 2) - 4, L'#');

	m_entMgr.createEnt((gScreenWidth / 2), (gScreenHeight / 2) - 3, L'#');
	m_entMgr.createEnt((gScreenWidth / 2) - 1, (gScreenHeight / 2) - 3, L'#');
	m_entMgr.createEnt((gScreenWidth / 2) + 1, (gScreenHeight / 2) - 3, L'#');

	m_entMgr.createEntSpecification<WanderingLouse>
		((gScreenWidth / 2) - 3, (gScreenHeight / 2) - 5);
	m_entMgr.createEntSpecification<Ghost>
		((gScreenWidth / 2) - 5, (gScreenHeight - 2));*/
	const MapDataArray& mapDat{ mapFile.getData() };
	// iterate through all the std::strings
	for (size_t i{ 0 }; i < mapDat.size(); i++)
	{
		// iterate through all the chars of the std::string
		for (size_t j{ 0 }; j < mapDat[i].size(); j++)
		{
			switch (mapDat[i][j])
			{
			case '#':
				m_entMgr.createEnt(j, i, '#');
				break;
			case 'p': // player spawn point
				m_player = m_entMgr.createPlayer(j, i, static_cast<wchar_t>(0x555));
				break;
			case 'e': // ghost enemy
				m_entMgr.createEntSpecification<Ghost>(j, i);
				break;
			default:
				break;
			}
		}
	}
}

void GameWindow::renderAllEntities()
{
	for (unsigned int i{ 0 }; i < m_entMgr.getArraySize(); i++)
	{
		const Entity* curEnt{ m_entMgr.getEntity(i) };
		if (curEnt)
			if (curEnt->getPos() <= gScreenTotalPxs)
				//m_screen[curEnt->getPos()] = curEnt->getTex();
				gPacMan.sendData(curEnt->getTex(), curEnt->getPos());
	}
}

const EntityMgr& GameWindow::getEntMgr() const
{
	return m_entMgr;
}

GameWindow::GameWindow(const MapFile& mapFile)
	: Window(WindowType::GameWindow)
{
	initEntities(mapFile);
	// m_state_begin isn't used for the GameWindow specifically, but
	// it should be updated anyway
	m_state_begin = false;
}