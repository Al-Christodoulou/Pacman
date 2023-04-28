#include "GameWindow.h"
#include "../PacMan.h"
#include "../Engine/Random.h"
#include "../WanderingLouse.h"
#include "../Player.h"
#include "../Ghost.h"
#include "../MapFile.h"

void GameWindow::render()
{
	gPacMan.fillscreen(L' ');
	renderAllEntities();

	switch (m_gameState)
	{
	case GameState::FreezeTime:
		gPacMan.swprintf_s(cSecondsTextOffset, 20, L"%.0f", cFreezeTime - m_gameTime);
		break;
	case GameState::Playing:
		gPacMan.swprintf_s(cPlayerLivesTextOffset, 15, L"Lives: %d", 2);
		gPacMan.swprintf_s(25, L"X: %.3f, Y: %.2f", m_player->getVirtualX(), m_player->getVirtualY());
		gPacMan.swprintf_s(gScreenWidth, 30, L"DT: %f", Engine::getDeltaTime());
		break;
	}
}

void GameWindow::runLogic()
{
	m_gameTime += Engine::getDeltaTime();

	switch (m_gameState)
	{
	case GameState::FreezeTime:
		if (cFreezeTime - m_gameTime < 0)
			m_gameState = GameState::Playing;
		break;
	case GameState::Playing:
		// make all characters think
		for (std::unique_ptr<Entity>& entPtr : m_entMgr.getEntities())
		{
			if (entPtr->getEntType() == EntityType::Character)
				static_cast<Character&>(*entPtr).think();
		}
		if (m_player->isDead())
			m_gameState = GameState::PlayerDead;
		break;
	case GameState::PlayerDead:
		break;
	}

	// if the player presses escape, the GameWindow will terminate and we go back to the
	// main menu
	if (gPacMan.isKeyTapped(VK_ESCAPE))
		m_state_terminate = true;
}

void GameWindow::initEntities(const MapFile& mapFile)
{
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
				m_player = m_entMgr.createCharacter<Player>(j, i, static_cast<wchar_t>(0x555));
				break;
			case 'e': // ghost enemy
				m_entMgr.createCharacter<Ghost>(j, i);
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