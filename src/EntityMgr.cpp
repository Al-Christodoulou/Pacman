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
	ConstEntityArrayIterator iter{ m_entities.begin() };
	while (iter != m_entities.end())
	{
		// touch functions might (for the case of Player touching a pickup) remove an
		// entity from m_entities, therefore this loop should not increment the index
		const size_t previousTotalEntities{ m_entities.size() };
		
		// make sure we don't check against the same character
		if (**iter != static_cast<Entity&>(character) && (**iter).getPos() == character.getPos())
		{
			ConstEntityArrayIterator prevIter{ iter };
			character.touch(iter); // this might delete the entity pointed to by iter
			iter = prevIter;

			if ((**iter).getEntType() == EntityType::Character)
			{
				Character* const curChar{ static_cast<Character* const>(&**iter) };
				curChar->touch(iter);

				// we have a violation (and the entity wasn't deleted), return true
				return true;
			}
		}

		// if the total amount of entities hasn't changed, then increment the index
		if (m_entities.size() == previousTotalEntities)
			++iter;
	}
	return false;
}