#include "Ghost.h"
#include "EntityMgr.h"
#include "PacMan.h"

#ifdef LOG_ENABLED
#include <string>
#endif

void Ghost::think()
{
	if (m_targetPlayer) // if we found him
	{
		// if the player can eat this Ghost, this float will
		// be 1.0f, else -1.0f. this is to make the Ghosts move
		// away from the player to immitate "fear" behavior
		const float getAwayMultiplier{
			!m_targetPlayer->canEatEnemies() ? 1.0f : -1.0f
		};

		if ((m_x - m_targetPlayer->getVirtualX()) * getAwayMultiplier > 0)
			moveLeft();
		else
			moveRight();

		if ((m_y - m_targetPlayer->getVirtualY()) * getAwayMultiplier > 0)
			moveUp();
		else
			moveDown();
	}
}

void Ghost::touch(const ConstEntityArrayIterator& iter)
{
	// TODO: this isn't needed, instead make Character have a default
	// empty touch method
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

	Engine::Log << "m_targetPlayer is: " << std::to_string((int)m_targetPlayer) << "\n";
	Engine::Log.flush();
}

Ghost::Ghost(int x, int y, float extraSpeed)
	: Character(x, y, L'&', EntityType::Ghost)
{
	setSpeed(10.0f + extraSpeed);
}