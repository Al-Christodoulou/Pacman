#include "GameWindow.h"
#include "MessageWindow.h"
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
	gPacMan.swprintf_s(cPlayerLivesTextOffset, 20, L"Lives: %d", m_player->getLives());

	switch (m_gameState)
	{
	case GameState::FreezeTime:
		gPacMan.swprintf_s(cSecondsTextOffset, 20, L"%.0f", cFreezeTime - m_gameTime);
		break;
	case GameState::Playing:
		gPacMan.swprintf_s(25, L"X: %.3f, Y: %.2f", m_player->getVirtualX(), m_player->getVirtualY());
		gPacMan.swprintf_s(gScreenWidth, 30, L"DT: %f", Engine::getDeltaTime());
		break;
	case GameState::PlayerDead:
		gPacMan.swprintf_s(cSecondsTextOffset, 16, L"YOU ARE DEAD!");
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
	{
		// make all characters think
		EntityArray& entities{ m_entMgr.getEntities() };
		size_t i{ 0 };
		while (i < entities.size())
		{
			size_t previousSize{ entities.size() };
			if (entities[i]->getEntType() == EntityType::Character)
				static_cast<Character&>(*entities[i]).think();

			// since m_entities can be modified through think() (due to it
			// calling a series of functions leading to checkViolationFor),
			// if some entity was deleted, the one after took its place, so
			// the index should not update in this iteration of the loop!
			if (previousSize == entities.size())
				i++;
		}
		if (m_player->isDead())
		{
			m_resetTimestamp = m_gameTime + 2.0f;
			m_gameState = GameState::PlayerDead;
		}
		break;
	}
	case GameState::PlayerDead:
		if (m_gameTime > m_resetTimestamp)
		{
			m_player->decreaseLives();
			// if the game's lost, popup a message and quit the map
			if (m_player->getLives() == 0)
			{
				m_state_terminate = true;
				gPacMan.getWindowMgr().pushAnyWindow<MessageWindow>(24, 7, L"You lost the game...", L"");
				return;
			}
			restartRound();
		}
		break;
	}

	// if the player presses escape, the GameWindow will terminate and we go back to the
	// main menu
	if (gPacMan.isKeyTapped(VK_ESCAPE))
		m_state_terminate = true;
}

void GameWindow::initEntities(unsigned int plNumOfLives)
{
	const MapDataArray& mapDat{ m_mapFile.getData() };
	// iterate through all the std::strings
	for (size_t i{ 0 }; i < mapDat.size(); i++)
	{
		// iterate through all the chars of the std::string
		for (size_t j{ 0 }; j < mapDat[i].size(); j++)
		{
			switch (mapDat[i][j])
			{
			case '#':
				m_entMgr.createDefaultEnt(j, i, '#');
				break;
			case 'p': // player spawn point
				m_player = m_entMgr.createCharacter<Player>(j, i, static_cast<wchar_t>(0x555), plNumOfLives);
				break;
			case 'e': // ghost enemy
				m_entMgr.createCharacter<Ghost>(j, i);
				break;
			case '.': // dot that pacman can eat
				m_entMgr.createCustomBaseEnt(EntityType::Dot, j, i, static_cast<wchar_t>(L'\u25aa'));
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

void GameWindow::restartRound()
{
	m_gameTime = 0.0f;
	m_resetTimestamp = 0.0f;
	// get the player lives before this entity gets deleted by clear()
	unsigned int playerLives{ m_player->getLives() };
	m_entMgr.getEntities().clear();
	initEntities(playerLives);
	m_gameState = GameState::FreezeTime;
}

EntityMgr& GameWindow::getEntMgr()
{
	return m_entMgr;
}

GameWindow::GameWindow(const MapFile& mapFile)
	: Window(WindowType::GameWindow), m_mapFile{ mapFile }
{
	initEntities();
	// m_state_begin isn't used for the GameWindow specifically, but
	// it should be updated anyway
	m_state_begin = false;
}