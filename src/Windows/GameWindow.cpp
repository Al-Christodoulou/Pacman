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
	gPacMan.swprintf_s(cPlayerScoreTextOffset, 20, L"Score: %d", m_player->getScore());

	switch (m_gameState)
	{
	case GameState::FreezeTime:
		gPacMan.swprintf_s(cInfoTextOffset, 20, L"%.0f", cFreezeTime - m_gameTime);
		break;
	case GameState::Playing:
#ifdef _DEBUG
		gPacMan.swprintf_s(25, L"X: %.3f, Y: %.2f", m_player->getVirtualX(), m_player->getVirtualY());
		gPacMan.swprintf_s(gScreenWidth, 30, L"DT: %f", Engine::getDeltaTime());
#endif
		gPacMan.swprintf_s(cInfoTextOffset, 25, L"Round: %d", m_currentRound);
		break;
	case GameState::PlayerDead:
		gPacMan.swprintf_s(cInfoTextOffset, 16, L"YOU ARE DEAD!");
		break;
	case GameState::RoundWon:
		gPacMan.swprintf_s(cInfoTextOffset, 25, L"You won the round!");
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
			Engine::Log << "Entity #" << i << "'s (" << (int)(&*entities[i]) << ") thinking...\n";

			if (entities[i]->getEntType() == EntityType::Ghost ||
				entities[i]->getEntType() == EntityType::Player)
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
		// if the player ate all the dots, he won the round
		if (m_player->getDotsEatenCount() == m_totalDotCount)
		{
			m_resetTimestamp = m_gameTime + 2.0f;
			m_gameState = GameState::RoundWon;
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
			restartGame();
		}
		break;
	case GameState::RoundWon:
		if (m_gameTime > m_resetTimestamp)
		{
			restartRound();
		}
		break;
	}

	// if the player presses escape, the GameWindow will terminate and we go back to the
	// main menu
	if (gPacMan.isKeyTapped(VK_ESCAPE))
		m_state_terminate = true;
}

void GameWindow::postMoveInit()
{
	initRound();
}

void GameWindow::initRound(unsigned int plNumOfLives)
{
	m_totalDotCount = 0;
	const MapDataArray& mapDat{ m_mapFile.getData() };
	// iterate through all the std::strings
	for (size_t i{ 0 }; i < mapDat.size(); i++)
	{
		// iterate through all the chars of the std::string
		for (size_t j{ 0 }; j < mapDat[i].size(); j++)
		{
			switch (mapDat[i][j])
			{
			case '#': // wall
				m_entMgr.createDefaultEnt(j, i, '#');
				break;
			case 'p': // player spawn point
				m_player = m_entMgr.createCharacter<Player>(j, i, static_cast<wchar_t>(0x555), plNumOfLives);
				break;
			case 'e': // ghost enemy
				m_entMgr.createCharacter<Ghost>(j, i, cRoundGhostSpeedBoost * m_currentRound - 1);
				break;
			case '.': // dot that pacman can eat
				m_entMgr.createCustomBaseEnt(EntityType::Dot, j, i, static_cast<wchar_t>(L'\u25aa'));
				m_totalDotCount++;
				break;
			case '@': // powerup
				m_entMgr.createCustomBaseEnt(EntityType::Powerup, j, i, static_cast<wchar_t>(L'\u2663'));
				break;
			default:
				break;
			}
		}
	}

	// call init() on all characters
	for (auto& ent : m_entMgr.getEntities())
	{
		if (ent->getEntType() == EntityType::Ghost ||
			ent->getEntType() == EntityType::Player)
		{
			static_cast<Character&>(*ent).init();
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

void GameWindow::restartGame()
{
	innerRestart(false);
}

void GameWindow::restartRound()
{
	innerRestart(true);
}

// if restartRound == false, then we restart the game instead
void GameWindow::innerRestart(bool restartRound)
{
	Engine::Log << "*** Restart ***";
	Engine::Log.flush();

	m_gameTime = 0.0f;
	m_resetTimestamp = 0.0f;
	const unsigned int newPlayerLivesValue{
		restartRound ? Player::Lives : m_player->getLives()
	};
	m_entMgr.getEntities().clear();

	restartRound ? m_currentRound++ : m_currentRound = 1;
	initRound(newPlayerLivesValue);
	m_gameState = GameState::FreezeTime;
}

EntityMgr& GameWindow::getEntMgr()
{
	return m_entMgr;
}

float GameWindow::getGameTime() const
{
	return m_gameTime;
}

unsigned int GameWindow::getRound() const
{
	return m_currentRound;
}

GameWindow::GameWindow(const MapFile& mapFile)
	: Window(WindowType::GameWindow), m_mapFile{ mapFile }
{
	// m_state_begin isn't used for the GameWindow specifically, but
	// it should be updated anyway
	m_state_begin = false;
}