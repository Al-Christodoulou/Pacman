#include <utility>
#include "EntityMgr.h"

const Entity* const EntityMgr::getEntity(unsigned int index) const
{
	return index <= m_entities.size() - 1 ? m_entities[index].get() : nullptr;
	//return m_entities[index].get();
}

// had to remove the const from this so GameWindow can change the entities
EntityArray& EntityMgr::getEntities()
{
	return m_entities;
}

const Entity* const EntityMgr::searchEntity(bool (*criteria)(const std::unique_ptr<Entity>& ent)) const
{
	auto iterator{ std::find_if(m_entities.begin(), m_entities.end(), criteria) };
	/*if (iterator != std::end(m_entities))
		return (*iterator).get();
	else
		return nullptr;*/
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
bool EntityMgr::checkViolationFor(Character& character) const
{
	for (auto& curEnt : m_entities)
	{
		// a dangerous cast
		Character* curChar{ static_cast<Character*>(curEnt.get()) };
		// make sure we don't check against the same character
		if (*curChar != character && curChar->getPos() == character.getPos())
		{
			if (curChar->getEntType() == EntityType::Character)
			{
				curChar->touch(character);
				character.touch(*curChar);
			}
			// if we have a violation, return true
			return true;
		}
	}
	return false;
}