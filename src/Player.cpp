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

void Player::touch(Character& other)
{
}

Player::Player(int x, int y, wchar_t texture)
	: Character{ x, y, texture }
{}

Player::Player(wchar_t texture)
	: Character{ texture }
{}