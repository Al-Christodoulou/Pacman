#pragma once
#include <chrono>
#include "Character.h"

class Ghost : public Character
{
private:
	static constexpr inline int cUpdateMoveDirDelay{ 200 };
	timep_t m_updateMoveDirTimestamp{ std::chrono::system_clock::now() };
	enum class MoveDir
	{
		UP, DOWN, LEFT, RIGHT,
		max_actions
	} m_movedir{ MoveDir::LEFT };

public:
	void think() override;

	Ghost(int, int);
};