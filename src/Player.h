#pragma once
#include "Character.h"

class Player : public Character
{
private:
	unsigned int m_numOfLives;
	unsigned int m_score{ 0 };
	bool m_isDead{ false };

public:
	void think() override;
	void touch(Character&) override;
	void decreaseLives();
	void increaseScore(unsigned int);
	unsigned int getLives();
	bool isDead();

	Player(int, int, wchar_t, unsigned int = 3);
	Player(wchar_t, unsigned int = 3);
};