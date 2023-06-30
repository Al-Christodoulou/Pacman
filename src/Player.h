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
	unsigned int getScore() const;
	unsigned int getLives() const;
	bool isDead() const;

	Player(int, int, wchar_t, unsigned int = 3);
};