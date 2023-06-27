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
	for (auto& curEnt : m_entities)
	{
		// TODO: make this better
		size_t index{ 0 };

		// make sure we don't check against the same character
		if (*curEnt != static_cast<Entity&>(character) && curEnt->getPos() == character.getPos())
		{
			if (curEnt->getEntType() == EntityType::Character)
			{
				Character* curChar{ static_cast<Character*>(curEnt.get()) };
				curChar->touch(character);
				character.touch(*curChar);
			}
			// if this is the player and he touched a dot
			if (character.getTex() == static_cast<wchar_t>(0x555) && curEnt->getEntType() == EntityType::Dot)
			{
				auto iter{ std::next(m_entities.begin(), index) };
				m_entities.erase(iter);
				// move the rest of the entities one step back so this empty slot is filled
				// TODO: this causes crashes at the moment!
				for (size_t i{ index }; i < m_entities.size() - 1; i++)
				{
					m_entities[i] = std::move(m_entities[i + 1]);
				}
			}
			// if we have a violation, return true
			return true;
		}

		++index;
	}
	return false;
}