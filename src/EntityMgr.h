#pragma once
#include <array>
#include "Engine/Engine.h"
#include "Engine/UniquePtrUtils.h"
#include "Character.h"
#include "Player.h"
#include "EntityMgrTypedefs.h"

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
	std::weak_ptr<Entity> pushAnyEnt(std::unique_ptr<T> anyEnt)
	{
		// upcast T to Entity. if T isn't part of the Entity hierarchy, the
		// static assertion in createAnyEnt below will have failed by now
		Entity* upcastedEnt{ static_cast<Entity*>(anyEnt.release()) };

		return m_entities.emplace_back(std::move(std::shared_ptr<Entity>(upcastedEnt)));
	}

	// create an entity specification of type T (Wandering Louse, Ghost etc.)
	template <typename T = Entity, typename... Args>
	std::weak_ptr<Entity> createAnyEnt(Args... args)
	{
		static_assert(!std::is_pointer_v<T> && !std::is_reference_v<T>,
			"T must not be a pointer or a reference type!");
		static_assert(std::is_base_of_v<Entity, T>, "Not part of the Entity hierarchy!");

		// create a UNIQUE pointer of type T so we can upcast it to an Entity and then
		// create the actual shared pointer of type Entity to return it
		// this is done because a shared pointer cannot be upcasted (since it's shared,
		// shared pointers can't be "released" like simple unique pointers
		return pushAnyEnt(std::move(std::make_unique<T>(args...)));
	}

public:
	const Entity* const getEntity(unsigned int) const;
	EntityArray& getEntities();
	// search for an entity based on a given criteria
	const Entity* const searchEntity(bool (*)(const SharedEntityPtr&)) const;

	unsigned int getArraySize() const; // NOTE: not really required, could just
									// use gScreenTotalPxs

	template <typename... Args>
	std::weak_ptr<Entity> createDefaultEnt(Args... args)
	{
		return createAnyEnt<Entity>(args..., EntityType::Default);
	}

	// create an Entity whose EntityType != default 
	template <typename... Args>
	std::weak_ptr<Entity> createCustomBaseEnt(EntityType enttype, Args... args)
	{
		return createAnyEnt<Entity>(args..., enttype);
	}

	template <typename CharType, typename... Args>
	std::weak_ptr<Entity> createCharacter(Args... args)
	{
		static_assert(std::is_base_of_v<Character, CharType>, "Not a character!");
		return createAnyEnt<CharType>(args...);
	}

	void moveEnt(SharedEntityPtr&);
	void deleteEntity(const ConstEntityArrayIterator);

	// no copying or moving of EntityMgr is allowed
	EntityMgr(const EntityMgr&) = delete;
	EntityMgr(EntityMgr&&) = delete;
	EntityMgr() = default;

	bool checkViolationFor(Character&);
	bool performCollisionTouch(Character&, const ConstEntityArrayIterator&);
};