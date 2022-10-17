#include <Windows.h>
#include "Player.h"

void Player::think()
{
	if (GetAsyncKeyState(L'W' & 0x8000))
		moveUp();
}

Player::Player(int x, int y, wchar_t texture)
	: Character{ x, y, texture }
{}

Player::Player(wchar_t texture)
	: Character{ texture }
{}