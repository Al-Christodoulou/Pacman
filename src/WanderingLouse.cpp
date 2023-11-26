#include "WanderingLouse.h"
#include "Engine/Random.h"

void WanderingLouse::think()
{
	switch (m_movedir)
	{
	case MoveDir::UP:
		moveUp(); break;
	case MoveDir::DOWN:
		moveDown(); break;
	case MoveDir::LEFT:
		moveLeft(); break;
	case MoveDir::RIGHT:
		moveRight(); break;
	}

	if (std::chrono::system_clock::now() > m_updateMoveDirTimestamp)
	{
		m_updateMoveDirTimestamp = std::chrono::system_clock::now() + std::chrono::milliseconds(cUpdateMoveDirDelay);
		MoveDir newMoveDir{ static_cast<MoveDir>(Random::get(0, static_cast<int>(MoveDir::max_actions) - 1)) };
		m_movedir = newMoveDir;
	}
}

void WanderingLouse::touch(const ConstEntityArrayIterator&) {}
void WanderingLouse::init() {}

WanderingLouse::WanderingLouse(int x, int y)
	: Character{ x, y, L'@', EntityType::Default }
{}