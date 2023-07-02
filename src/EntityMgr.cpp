#include <utility>
#include "EntityMgr.h"

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

/*
* Checks if two entities lie in the same position. if so, then we have a
* violation and this returns true
*/
bool EntityMgr::checkViolationFor(Character& character)
{
	size_t index{ 0 };
	while (index < m_entities.size())
	{
		// touch functions might (for the case of Player touching a pickup) remove an
		// entity from m_entities, therefore this loop should not increment the index
		const size_t previousTotalEntities{ m_entities.size() };
		
		Entity& curEnt{ *m_entities[index] };
		// make sure we don't check against the same character
		if (curEnt != static_cast<Entity&>(character) && curEnt.getPos() == character.getPos())
		{
			character.touch(curEnt);
			if (curEnt.getEntType() == EntityType::Character)
			{
				Character* const curChar{ static_cast<Character* const>(&curEnt) };
				curChar->touch(character);
			}
			// we have a violation, return true
			return true;
		}

		// if the total amount of entities hasn't changed, then increment the index
		if (m_entities.size() == previousTotalEntities)
			++index;
	}
	return false;
}