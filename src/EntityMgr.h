#pragma once
#include <array>
#include <vector>
#include <memory>
#include "Engine.h"
#include "Entity.h"
#include "Character.h"
#include "Player.h"
#include "Ghost.h"

class EntityMgr
{
private:
	using EntityArray = std::vector<std::unique_ptr<Entity>>;
	EntityArray m_entities{};

	// takes a Player, Ghost, ... pointer and upcasts it to an Entity
	// pointer in order to be able to move it inside m_entities
	template <typename T>
	std::unique_ptr<Entity> upcastToEnt(std::unique_ptr<T>& e)
	{
		static_assert(std::is_convertible_v<T, Entity>,
			"T must be part of the Entity hierarchy!");
		Entity* entPtr{ static_cast<Entity*>(e.release()) };
		return std::unique_ptr<Entity>{ entPtr };
	}

public:
	const Entity* const getEntity(unsigned int) const;
	unsigned int getArraySize() const; // NOTE: not really required, could just
									// use gScreenTotalPxs

	Entity* createEnt(int, int, wchar_t);
	Entity* createEnt(wchar_t);
	Entity* pushEnt(std::unique_ptr<Entity>);

	Player* createPlayer(int, int, wchar_t);
	Player* createPlayer(wchar_t);
	Player* pushPlayer(std::unique_ptr<Player>);

	// create an entity specification of type T (Wandering Louse, Ghost etc.),
	// cast it to an Entity, push it to m_entities and return the pointer to it
	template <typename T>
	T* createEntSpecification(int x, int y)
	{
		std::unique_ptr<T> entSpec{ std::make_unique<T>(x, y) };
		std::unique_ptr<Entity> entUpcast{ upcastToEnt(entSpec) };

		m_entities.push_back(std::move(entUpcast));
		return static_cast<T*>(m_entities[m_entities.size() - 1].get());
	}

	// no copying or moving of EntityMgr is allowed
	EntityMgr(const EntityMgr&) = delete;
	EntityMgr(EntityMgr&&) = delete;
	EntityMgr() = default;

	// maybe temporary
	bool checkViolationFor(const Character&);
};

// EntityMgr is a global variable so each character can easily call its methods
extern EntityMgr gEntMgr;