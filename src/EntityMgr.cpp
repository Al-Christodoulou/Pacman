#include <utility>
#include "EntityMgr.h"

EntityMgr gEntMgr{};

const Entity* const EntityMgr::getEntity(unsigned int index) const
{
	return m_entities[index].get();
}

const EntityArray& EntityMgr::getEntities() const
{
	return m_entities;
}

const Entity* const EntityMgr::searchEntity(bool (*criteria)(const std::unique_ptr<Entity>& ent))
{
	auto iterator{ std::find_if(m_entities.begin(), m_entities.end(), criteria) };
	if (iterator != std::end(m_entities))
		return (*iterator).get();
	else
		return nullptr;
}

unsigned int EntityMgr::getArraySize() const
{
	return m_entities.size();
}

Entity* EntityMgr::createEnt(int x, int y, wchar_t texture)
{
	return pushAnyEnt(std::move(std::make_unique<Entity>(x, y, texture, Entity::EntityType::Default)));
}

Entity* EntityMgr::createEnt(wchar_t texture)
{
	return pushAnyEnt(std::move(std::make_unique<Entity>(texture, Entity::EntityType::Default)));
}

Player* EntityMgr::createPlayer(int x, int y, wchar_t texture)
{
	return pushAnyEnt(std::move(std::make_unique<Player>(x, y, texture)));
}

Player* EntityMgr::createPlayer(wchar_t texture)
{
	return pushAnyEnt(std::move(std::make_unique<Player>(texture)));
}

/*
* Checks if two entities lie in the same position. if so, then we have a
* violation and this returns true
*/
bool EntityMgr::checkViolationFor(const Character& character)
{
	for (const auto& curEnt : m_entities)
	{
		// make sure we don't check against the same character
		if (*static_cast<Character*>(curEnt.get()) != character)
		{
			// if we have a violation, return true
			if (curEnt.get()->getPos() == character.getPos())
				return true;
		}
	}
	return false;
}