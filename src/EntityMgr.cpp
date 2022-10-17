#include <utility>
#include "EntityMgr.h"

// TODO: fix the compile error
// HACK: convert from unique_ptr<Player> to unique_ptr<Entity> (without losing
// the data)
std::unique_ptr<Entity> EntityMgr::convPlyToEnt(std::unique_ptr<Character> uniPtrChar)
{
	Entity* entPtr{ static_cast<Entity*>(uniPtrChar.release()) };
	return std::unique_ptr<Entity>{ entPtr };
}

const Entity* const EntityMgr::getEntity(unsigned int index) const
{
	return m_entities[index].get();
}

unsigned int EntityMgr::getArraySize() const
{
	return m_entities.size();
}

Entity* EntityMgr::createEnt(int x, int y, wchar_t texture)
{
	m_entities.push_back(std::make_unique<Entity>(x, y, texture));
	return m_entities[m_entities.size() - 1].get();
}

Entity* EntityMgr::createEnt(wchar_t texture)
{
	m_entities.push_back(std::make_unique<Entity>(texture));
	return m_entities[m_entities.size() - 1].get();
}

Player* EntityMgr::createPlayer(int x, int y, wchar_t texture)
{
	std::unique_ptr<Entity> entUniPtr{ convPlyToEnt(std::make_unique<Player>(x, y, texture)) };

	m_entities.push_back(entUniPtr);
	return static_cast<Player*>(m_entities[m_entities.size() - 1].get());
}

Player* EntityMgr::createPlayer(wchar_t texture)
{
	std::unique_ptr<Entity> entUniPtr{ convPlyToEnt(std::make_unique<Player>(texture)) };

	m_entities.push_back(entUniPtr);
	return static_cast<Player*>(m_entities[m_entities.size() - 1].get());
}

/*EntityMgr::EntityMgr()
{
	for (int i{ 0 }; i < m_entities.size(); i++)
	{
		m_entities[i] = nullptr;
	}
}*/