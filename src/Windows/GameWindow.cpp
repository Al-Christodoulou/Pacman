#include "GameWindow.h"
#include "MessageWindow.h"
#include "../PacMan.h"
#include "../Engine/Random.h"
#include "../WanderingLouse.h"
#include "../Player.h"
#include "../Ghost.h"
#include "../MapFile.h"

Player* const GameWindow::getPlayer() const
{
	return static_cast<Player* const>(m_player.get());
}

void GameWindow::render()
{
	gPacMan.fillscreen(L' ');
	renderAllEntities();

	gPacMan.swprintf_s(cPlayerLivesTextOffset, 20, L"Lives: %d", getPlayer()->getLives());
	gPacMan.swprintf_s(cPlayerScoreTextOffset, 20, L"Score: %d", getPlayer()->getScore());

	switch (m_gameState)
	{
	case GameState::FreezeTime:
	{
		int intTimeMult10{ static_cast<int>((cFreezeTime - m_gameTime) * 10) };
		// small optimization hack so std::to_wstring isn't called every frame
		// but only when the integer part of cFreezeTime - m_gameTime changes
		if (intTimeMult10 % 10 == 0)
			m_infoWindow.setMessage(L"Starting in " + std::to_wstring(static_cast<int>
				(cFreezeTime - m_gameTime))
			);
		m_infoWindow.render();
		break;
	}
	case GameState::Playing:
#ifdef _DEBUG
		gPacMan.swprintf_s(25, L"X: %.3f, Y: %.2f",
			getPlayer()->getVirtualX(),
			getPlayer()->getVirtualY()
		);
		gPacMan.swprintf_s(gScreenWidth, 30, L"DT: %f", Engine::getDeltaTime());
#endif
		gPacMan.swprintf_s(cInfoTextOffset, 25, L"Round: %d", m_currentRound);
		break;
	case GameState::PlayerDead:
		m_infoWindow.setMessage(L"You are dead!");
		m_infoWindow.render();
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
			Engine::Log << "Entity #" << i << "'s (" << (int)(&*entities[i]) << ") thinking...\n";

			if (entities[i]->getEntType() == EntityType::Ghost ||
				entities[i]->getEntType() == EntityType::Player)
				static_cast<Character&>(*entities[i]).think();

			// if we're about to go out of bounds (because think() deleted an entity),
			// stop here
			if (i == entities.size())
				break;

			// delete this Ghost if the Player has eaten it
			if (entities[i]->getEntType() == EntityType::Ghost &&
				static_cast<Character&>(*entities[i]).isDead())
			{
				// quite a slow way of doing things
				ConstEntityArrayIterator iter{ m_entMgr.getEntities().begin() };
				while (**iter != *entities[i] && iter != m_entMgr.getEntities().end())
					++iter;
				m_entMgr.deleteEntity(iter);
			}
			else
				i++;
		}
		if (getPlayer()->isDead())
		{
			m_resetTimestamp = m_gameTime + 2.0f;
			m_gameState = GameState::PlayerDead;
		}
		// if the player ate all the dots, he won the round
		if (getPlayer()->getDotsEatenCount() == m_totalDotCount)
		{
			m_resetTimestamp = m_gameTime + 2.0f;
			m_gameState = GameState::RoundWon;
		}
		break;
	}
	case GameState::PlayerDead:
		if (m_gameTime > m_resetTimestamp)
		{
			getPlayer()->decreaseLives();
			// if the game's lost, popup a message and quit the map
			if (getPlayer()->getLives() == 0)
			{
				m_state_terminate = true;
				gPacMan.getWindowMgr().pushAnyWindow<MessageWindow>(24, 7, 0, 0, L"You lost the game...", L"");
				return;
			}
			restartRound(false);
		}
		break;
	case GameState::RoundWon:
		if (m_gameTime > m_resetTimestamp)
		{
			restartRound(true);
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

void GameWindow::initRound()
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
				if (!m_player)
				{
					m_player = std::shared_ptr{
						m_entMgr.createCharacter<Player>(j, i, static_cast<wchar_t>(0x555))
					};
				}
				else
				{
					getPlayer()->roundReset(j, i);
					m_entMgr.moveEnt(m_player);
				}
				break;
			case 'e': // ghost enemy
				m_entMgr.createCharacter<Ghost>(j, i, cRoundGhostSpeedBoost * m_currentRound - 1);
				break;
			case '.': // dot that pacman can eat
			{
				const auto setIter{ m_blacklistedDotPositions.find(j + i * gScreenWidth) };
				if (setIter == m_blacklistedDotPositions.end())
				{
					m_entMgr.createCustomBaseEnt(EntityType::Dot, j, i, static_cast<wchar_t>(L'\u25aa'));
					m_totalDotCount++;
				}
				break;
			}
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

void GameWindow::restartRound(bool roundWon)
{
	Engine::Log << "*** Restart ***";
	Engine::Log.flush();

	m_gameTime = 0.0f;
	m_resetTimestamp = 0.0f;
	const unsigned int playerLivesValue{ getPlayer()->getLives() };
	m_entMgr.getEntities().clear();

	if (roundWon)
	{
		m_currentRound++;
		// if all dots were eaten, reset
		if (m_blacklistedDotPositions.size() >= m_totalDotCount)
			m_blacklistedDotPositions.clear();
	}
	initRound();
	m_gameState = GameState::FreezeTime;
}

void GameWindow::addBlacklistedDotPos(const Entity& ent)
{
	m_blacklistedDotPositions.insert(ent.getPos());
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