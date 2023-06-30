#include <Windows.h>
#include "PacMan.h"
#include "Player.h"

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

void Player::touch(Character&)
{
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