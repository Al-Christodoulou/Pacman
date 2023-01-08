#pragma once
#include <array>
#include <vector>
#include <memory>
#include "Engine.h"
#include "Entity.h"
#include "Character.h"
#include "Player.h"

class EntityMgr
{
private:
	using EntityArray = std::vector<std::unique_ptr<Entity>>;
	EntityArray m_entities{};

	std::unique_ptr<Entity> convPlyToEnt(std::unique_ptr<Player>&);

public:
	const Entity* const getEntity(unsigned int) const;
	unsigned int getArraySize() const; // NOTE: not really required, could just
									// use gScreenTotalPxs

	Entity* createEnt(int, int, wchar_t);
	Entity* createEnt(wchar_t);

	Player* createPlayer(int, int, wchar_t);
	Player* createPlayer(wchar_t);

	// maybe temporary
	void checkViolationFor(Character&);
};

// EntityMgr is a global variable so each character can easily call its methods
extern EntityMgr gEntMgr;