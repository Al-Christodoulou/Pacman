#pragma once
#include "Character.h"

class Player : public Character
{
public:
	void think() override;
	void touch(Character&) override;

	Player(int, int, wchar_t);
	Player(wchar_t);
};