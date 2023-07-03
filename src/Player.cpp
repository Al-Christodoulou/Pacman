#include <Windows.h>
#include "PacMan.h"
#include "Player.h"
#include "EntityMgr.h"

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
}

void Player::touch(const ConstEntityArrayIterator& entIter)
{
	if ((**entIter).getEntType() == EntityType::Dot)
	{
		increaseScore(10);
		EntityMgr* entmgr{ gPacMan.getWindowMgr().tryGetEntMgr() };

		entmgr->deleteEntity(entIter);
	}
	else if ((**entIter).getEntType() == EntityType::Character)
		m_isDead = true;
}

void Player::decreaseLives()
{
	--m_numOfLives;
}

void Player::increaseScore(unsigned int amt)
{
	m_score += amt;
}

unsigned int Player::getScore() const
{
	return m_score;
}

unsigned int Player::getLives() const
{
	return m_numOfLives;
}

bool Player::isDead() const
{
	return m_isDead;
}

Player::Player(int x, int y, wchar_t texture, unsigned int numOfLives)
	: Character{ x, y, texture, EntityType::Player }, m_numOfLives{ numOfLives }
{}