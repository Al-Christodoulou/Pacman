#pragma once
#include "Character.h"

class Player : public Character
{
public:
	void think() override;

	Player(wchar_t);
};