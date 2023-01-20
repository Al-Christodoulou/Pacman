#include "Ghost.h"
#include "EntityMgr.h"

void Ghost::think()
{
	auto is_player{ [](const std::unique_ptr<Entity>& ent) {
		// just check his texture for now
		return ent.get()->getTex() == 0x555;
	} };

	/*const EntityArray& entArray{gEntMgr.getEntities()};

	auto iterator{ std::find_if(entArray.begin(), entArray.end(), is_player) };
	if (iterator != std::end(entArray)) // we found him
	{
		if (m_x - (*iterator).get()->getVirtualX())
	}*/
	const Entity* const player{ gEntMgr.searchEntity(is_player) };
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

Ghost::Ghost(int x, int y)
	: Character(x, y, L'&')
{
	setSpeed(10.0f);
}