#pragma once
#include "Character.h"

class Player : public Character
{
private:
	unsigned int m_numOfLives{ 3 };
	bool m_isDead{ false };

public:
	void think() override;
	void touch(Character&) override;
	void decreaseLives();
	unsigned int getLives();
	bool isDead();

	Player(int, int, wchar_t);
	Player(wchar_t);
};