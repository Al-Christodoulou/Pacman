#include "Ghost.h"
#include "EntityMgr.h"
#include "PacMan.h"

void Ghost::think()
{
	auto is_player{ [](const std::unique_ptr<Entity>& ent) {
		return ent.get()->getEntType() == EntityType::Player;
	} };

	const Entity* const player{ gPacMan.getWindowMgr().tryGetEntMgr()->searchEntity(is_player) };
	if (player) // if we found him
	{
		if (m_x - player->getVirtualX() > 0)
			moveLeft();
		else
			moveRight();

		if (m_y - player->getVirtualY() > 0)
			moveUp();
		else
			moveDown();
	}
}

void Ghost::touch(const ConstEntityArrayIterator&) {}

Ghost::Ghost(int x, int y, float extraSpeed)
	: Character(x, y, L'&')
{
	setSpeed(10.0f + extraSpeed);
}