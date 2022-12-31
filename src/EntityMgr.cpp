#include <utility>
#include "EntityMgr.h"

std::unique_ptr<Entity> EntityMgr::convPlyToEnt(std::unique_ptr<Player>& uniPtrChar)
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
	m_entities.push_back(std::make_unique<Entity>(x, y, texture, Entity::EntityType::Default));
	return m_entities[m_entities.size() - 1].get();
}

Entity* EntityMgr::createEnt(wchar_t texture)
{
	m_entities.push_back(std::make_unique<Entity>(texture, Entity::EntityType::Default));
	return m_entities[m_entities.size() - 1].get();
}

Player* EntityMgr::createPlayer(int x, int y, wchar_t texture)
{
	std::unique_ptr<Player> ply{ std::make_unique<Player>(x, y, texture) };
	std::unique_ptr<Entity> entUniPtr{ convPlyToEnt(ply) };

	m_entities.push_back(std::move(entUniPtr));
	return static_cast<Player*>(m_entities[m_entities.size() - 1].get());
}

Player* EntityMgr::createPlayer(wchar_t texture)
{
	std::unique_ptr<Player> ply{ std::make_unique<Player>(texture) };
	std::unique_ptr<Entity> entUniPtr{ convPlyToEnt(ply) };

	m_entities.push_back(std::move(entUniPtr));
	return static_cast<Player*>(m_entities[m_entities.size() - 1].get());
}

void EntityMgr::checkViolationFor(Character& character)
{
	for (const auto& curEnt : m_entities)
	{
		// make sure we don't check against the same character
		if (*static_cast<Character*>(curEnt.get()) != character)
		{
			// if we have a violation, revert the last movement of character
			if (curEnt.get()->getPos() == character.getPos())
			{
				switch (character.getLastAction())
				{
				case Character::MoveAction::UP: character.moveDown();
					break;
				case Character::MoveAction::DOWN: character.moveUp();
					break;
				case Character::MoveAction::LEFT: character.moveRight();
					break;
				case Character::MoveAction::RIGHT: character.moveLeft();
					break;
				}
			}
		}
	}
}