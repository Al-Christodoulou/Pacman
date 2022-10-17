#include <Windows.h>
#include "Player.h"

void Player::think()
{
	if (GetAsyncKeyState(L'W' & 0x8000))
		moveUp();
}

Player::Player(wchar_t texture)
	: Character{ texture }
{}