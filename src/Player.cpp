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
		m_score += 10;
		m_numDotsEaten++;
		EntityMgr* entmgr{ gPacMan.getWindowMgr().tryGetEntMgr() };

		entmgr->deleteEntity(entIter);
	}
	else if ((**entIter).getEntType() == EntityType::Character)
		m_isDead = true;
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

Player::Player(int x, int y, wchar_t texture, unsigned int numOfLives)
	: Character{ x, y, texture, EntityType::Player }, m_numOfLives{ numOfLives }
{}