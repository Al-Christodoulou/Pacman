#include <utility>
#include "EntityMgr.h"

#ifdef LOG_ENABLED
#include "PacMan.h"
#include "Windows/GameWindow.h"
#endif

const Entity* const EntityMgr::getEntity(unsigned int index) const
{
	return index <= m_entities.size() - 1 ? m_entities[index].get() : nullptr;
}

// had to remove the const from this so GameWindow can change the entities
EntityArray& EntityMgr::getEntities()
{
	return m_entities;
}

const Entity* const EntityMgr::searchEntity(bool (*criteria)(const std::unique_ptr<Entity>& ent)) const
{
	auto iterator{ std::find_if(m_entities.begin(), m_entities.end(), criteria) };
	return iterator != std::end(m_entities) ? (*iterator).get() : nullptr;
}

unsigned int EntityMgr::getArraySize() const
{
	return m_entities.size();
}

void EntityMgr::deleteEntity(const ConstEntityArrayIterator iter)
{
#ifdef LOG_ENABLED
	const GameWindow* const gamewin{
		reinterpret_cast<const GameWindow*>(gPacMan.getWindowMgr().getTopWindow())
	};
	std::string line{ std::to_string(gamewin->getGameTime()) };
	line.reserve(80);
	line.append(" | Round ");
	line.append(std::to_string(gamewin->getRound()));
	line.append(" | Deleting entity at ");
	line.append(std::to_string(reinterpret_cast<int>(&**iter)));
	line.append("\n");
	line.append("=> Player's memory loc is at ");
	for (const auto& ent : m_entities)
		if (ent->getEntType() == EntityType::Player)
			line.append(std::to_string((int)&*ent));
	line.append("\n");
	Engine::Log << line;
	Engine::Log.flush();
	int address{ (int)(&**iter) };
#endif

	m_entities.erase(iter);

#ifdef LOG_ENABLED
	Engine::Log << "Entity at " << address << " deleted!\n";
	Engine::Log.flush();
#endif
}

/*
* Checks if two entities lie in the same position. if so, then we have a
* violation and this returns true (unless one of the two entities gets
* deleted. if any entity happens to be a Character, its touch() method
* is called
*/
bool EntityMgr::checkViolationFor(Character& character)
{
	ConstEntityArrayIterator iter{ m_entities.begin() };
	while (iter != m_entities.end())
	{
		// if we're not checking against the same entity, and the positions are equal, we have a
		// collision
		if (**iter != static_cast<Entity&>(character) && (**iter).getPos() == character.getPos())
			return performCollisionTouch(character, iter);

		++iter;
	}
	return false;
}

bool EntityMgr::performCollisionTouch(Character& character, const ConstEntityArrayIterator& iter)
{
	// touch functions might (for the case of Player touching pickups) remove an
	// entity from m_entities, therefore, this loop should not increment the iterator.
	// this variable is later used to check if a deletion indeed took place
	size_t previousTotalEntities{ m_entities.size() };
	character.touch(iter); // this might delete the entity pointed to by iter

	// if there was indeed a deletion, return false (because the other entity
	// got deleted, so there's no need to revert the position)
	if (m_entities.size() != previousTotalEntities)
		return false;

	// the check above needs to happen again after the next touch() call inside the
	// following if statement
	previousTotalEntities = m_entities.size();

	if ((**iter).getEntType() == EntityType::Ghost ||
		(**iter).getEntType() == EntityType::Player)
	{
		//Character* const curChar{ static_cast<Character* const>(&**iter) };
		//curChar->touch(iter);

		// BAD BAD BAD: find a way to make this better!
		ConstEntityArrayIterator oppositeIter{ m_entities.begin() };
		while (**oppositeIter != character && oppositeIter != m_entities.end())
			++oppositeIter;
		static_cast<Character&>(**iter).touch(oppositeIter);

		if (m_entities.size() != previousTotalEntities)
			return false;
	}
	// we have a collision and no deletion took place, return true
	return true;
}