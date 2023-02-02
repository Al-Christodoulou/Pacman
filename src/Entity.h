#pragma once
#include "Engine.h"

enum class EntityType
{
	Default,
	Character,
	max_entity_types
};

class Entity
{
protected:
	float m_x{ gScreenWidth / 2 }, m_y{ gScreenHeight / 2 };
	wchar_t m_texture{ L'#' };

	EntityType m_entitytype;

public:
	static unsigned int interpretXY(float, float);
	unsigned int getPos() const;
	float getVirtualX() const;
	float getVirtualY() const;
	wchar_t getTex() const;
	EntityType getEntType() const;

	Entity(int, int, wchar_t, EntityType);
	Entity(wchar_t, EntityType);
};