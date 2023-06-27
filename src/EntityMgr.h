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
	std::unique_ptr<Entity> upcastToEnt(std::unique_ptr<T> e)
	{
		return util::upcast<Entity, T>(std::move(e));
	}

	template <typename T>
	T* pushAnyEnt(std::unique_ptr<T> anyEnt)
	{
		std::unique_ptr<Entity> upcasted{ upcastToEnt(std::move(anyEnt)) };
		return static_cast<T*>(m_entities.emplace_back(std::move(upcasted)).get());
	}

	// create an entity specification of type T (Wandering Louse, Ghost etc.)
	template <typename T = Entity, typename... Args>
	T* createAnyEnt(Args... args)
	{
		return pushAnyEnt(std::move(std::make_unique<T>(args...)));
	}

public:
	const Entity* const getEntity(unsigned int) const;
	EntityArray& getEntities();
	// search for an entity based on a given criteria
	const Entity* const searchEntity(bool (*)(const std::unique_ptr<Entity>&)) const;

	unsigned int getArraySize() const; // NOTE: not really required, could just
									// use gScreenTotalPxs

	template <typename... Args>
	Entity* createDefaultEnt(Args... args)
	{
		return createAnyEnt<Entity>(args..., EntityType::Default);
	}

	// create an Entity whose EntityType != default 
	template <typename... Args>
	Entity* createCustomBaseEnt(EntityType enttype, Args... args)
	{
		return createAnyEnt<Entity>(args..., enttype);
	}

	template <typename CharType, typename... Args>
	CharType* createCharacter(Args... args)
	{
		static_assert(std::is_base_of_v<Character, CharType>, "Not a character!");
		return createAnyEnt<CharType>(args...);
	}

	// no copying or moving of EntityMgr is allowed
	EntityMgr(const EntityMgr&) = delete;
	EntityMgr(EntityMgr&&) = delete;
	EntityMgr() = default;

	// maybe temporary
	bool checkViolationFor(Character&) const;
};