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

unsigned int Player::getLives()
{
	return m_numOfLives;
}

bool Player::isDead()
{
	return m_isDead;
}

Player::Player(int x, int y, wchar_t texture, unsigned int numOfLives)
	: Character{ x, y, texture }, m_numOfLives{ numOfLives }
{}

Player::Player(wchar_t texture, unsigned int numOfLives)
	: Character{ texture }, m_numOfLives{ numOfLives }
{}