#pragma once
#include <array>
#include <vector>
#include <memory>
#include "Engine/Engine.h"
#include "Engine/UniquePtrUtils.h"
#include "Entity.h"
#include "Character.h"
#include "Player.h"

using EntityArray = std::vector<std::unique_ptr<Entity>>;

class EntityMgr
{
private:
	EntityArray m_entities{};

	// takes a Player, Ghost, ... pointer and upcasts it to an Entity
	// pointer in order to be able to move it inside m_entities
	template <typename T>
	std::unique_ptr<Entity> upcastToEnt(std::unique_ptr<T>& e)
	{
		return util::upcast<Entity, T>(e);
	}

public:
	const Entity* const getEntity(unsigned int) const;
	EntityArray& getEntities();
	// search for an entity based on a given criteria
	const Entity* const searchEntity(bool (*)(const std::unique_ptr<Entity>&)) const;

	unsigned int getArraySize() const; // NOTE: not really required, could just
									// use gScreenTotalPxs

	Entity* createEnt(int, int, wchar_t);
	Entity* createEnt(wchar_t);

	Player* createPlayer(int, int, wchar_t);
	Player* createPlayer(wchar_t);

	template <typename T>
	T* pushAnyEnt(std::unique_ptr<T> anyEnt)
	{
		// if T is Entity, no casting's needed
		if constexpr (std::is_same_v<T, Entity>)
		{
			m_entities.push_back(std::move(anyEnt));
			return m_entities[m_entities.size() - 1].get();
		}
		else // Ghost, etc.
		{
			std::unique_ptr<Entity> theEnt{ upcastToEnt(anyEnt) };
			m_entities.push_back(std::move(theEnt));
			return static_cast<T*>(m_entities[m_entities.size() - 1].get());
		}
	}

	// create an entity specification of type T (Wandering Louse, Ghost etc.),
	// as long as the constructor parameters for that entity are the defaults
	// (x and y positions)
	template <typename T>
	T* createEntSpecification(int x, int y)
	{
		return pushAnyEnt(std::move(std::make_unique<T>(x, y)));
	}

	// no copying or moving of EntityMgr is allowed
	EntityMgr(const EntityMgr&) = delete;
	EntityMgr(EntityMgr&&) = delete;
	EntityMgr() = default;

	// maybe temporary
	bool checkViolationFor(const Character&) const;
};