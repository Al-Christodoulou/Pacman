#include <Windows.h>
#include "Player.h"

void Player::think()
{
	if (GetAsyncKeyState(L'W') & 0x8000)
		moveUp();
	if (GetAsyncKeyState(L'A') & 0x8000)
		moveLeft();
	if (GetAsyncKeyState(L'S') & 0x8000)
		moveDown();
	if (GetAsyncKeyState(L'D') & 0x8000)
		moveRight();
}

Player::Player(int x, int y, wchar_t texture)
	: Character{ x, y, texture }
{}

Player::Player(wchar_t texture)
	: Character{ texture }
{}