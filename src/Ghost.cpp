#include "Ghost.h"
#include "EntityMgr.h"
#include "PacMan.h"

void Ghost::think()
{
	if (m_targetPlayer) // if we found him
	{
		if (m_x - m_targetPlayer->getVirtualX() > 0)
			moveLeft();
		else
			moveRight();

		if (m_y - m_targetPlayer->getVirtualY() > 0)
			moveUp();
		else
			moveDown();
	}
}

void Ghost::touch(const ConstEntityArrayIterator& iter)
{
	if ((**iter).getEntType() == EntityType::Player)
	{
		if (static_cast<Player&>(**iter).canEatEnemies())
			m_isDead = true;
	}
}

void Ghost::init()
{
	auto is_player{ [](const std::unique_ptr<Entity>& ent) {
		return ent.get()->getEntType() == EntityType::Player;
	} };

	const auto ent{ gPacMan.getWindowMgr().tryGetEntMgr()->searchEntity(is_player) };
	m_targetPlayer = static_cast<const Player*>(ent);
}

Ghost::Ghost(int x, int y, float extraSpeed)
	: Character(x, y, L'&', EntityType::Ghost)
{
	setSpeed(10.0f + extraSpeed);
}