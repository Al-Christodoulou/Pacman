#include <Windows.h>
#include "PacMan.h"
#include "Player.h"
#include "EntityMgr.h"
#include "Windows/GameWindow.h"

void Player::think()
{
	if (gPacMan.isKeyHeld(L'W'))
		moveUp();
	if (gPacMan.isKeyHeld(L'A'))
		moveLeft();
	if (gPacMan.isKeyHeld(L'S'))
		moveDown();
	if (gPacMan.isKeyHeld(L'D'))
		moveRight();

	const PacmanWindow* topWin{ gPacMan.getWindowMgr().getTopWindow() };
	if (topWin->getWindowType() == WindowType::GameWindow)
	{
		const GameWindow* gameWin{ static_cast<const GameWindow*>(topWin) };
		if (gameWin->getGameTime() > m_canEatEnemiesResetTimestamp)
			m_canEatEnemies = false;

		if (m_canEatEnemies)
		{
			float timeDelta{ gameWin->getGameTime() - m_canEatEnemiesResetTimestamp };
			if (static_cast<int>(timeDelta) % 2 == 0)
				setTex(static_cast<wchar_t>(0x555));
			else
				setTex(L'%');
		}
	}
}

void Player::touch(const ConstEntityArrayIterator& entIter)
{
	switch ((**entIter).getEntType())
	{
	case EntityType::Dot:
	{
		m_score += 10;
		m_numDotsEaten++;
		EntityMgr* entmgr{ gPacMan.getWindowMgr().tryGetEntMgr() };

		entmgr->deleteEntity(entIter);
		break;
	}
	case EntityType::Ghost:
		if (!m_canEatEnemies)
			m_isDead = true;
		break;
	case EntityType::Powerup:
	{
		m_canEatEnemies = true;
		const PacmanWindow* topWin{ gPacMan.getWindowMgr().getTopWindow() };
		if (topWin->getWindowType() == WindowType::GameWindow)
		{
			const GameWindow* gameWin{ static_cast<const GameWindow*>(topWin) };
			m_canEatEnemiesResetTimestamp = gameWin->getGameTime() + 10.0f;
		}
		break;
	}
	}
}

void Player::init() {}

void Player::decreaseLives()
{
	--m_numOfLives;
}

unsigned int Player::getScore() const
{
	return m_score;
}

unsigned int Player::getLives() const
{
	return m_numOfLives;
}

unsigned int Player::getDotsEatenCount() const
{
	return m_numDotsEaten;
}

bool Player::canEatEnemies() const
{
	return m_canEatEnemies;
}

Player::Player(int x, int y, wchar_t texture, unsigned int numOfLives)
	: Character{ x, y, texture, EntityType::Player }, m_numOfLives{ numOfLives }
{}