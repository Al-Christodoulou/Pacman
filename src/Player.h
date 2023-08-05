#pragma once
#include "Character.h"

class Player : public Character
{
private:
	unsigned int m_numOfLives;
	unsigned int m_score{ 0 };
	unsigned int m_numDotsEaten{ 0 };

public:
	static constexpr unsigned int Lives{ 3 };

	void think() override;
	void touch(const ConstEntityArrayIterator&) override;
	void decreaseLives();
	unsigned int getScore() const;
	unsigned int getLives() const;
	unsigned int getDotsEatenCount() const;

	Player(int, int, wchar_t, unsigned int = Lives);
};