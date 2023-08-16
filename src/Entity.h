#pragma once
#include "Engine/Engine.h"

enum class EntityType
{
	Default,
	Player,
	Ghost,
	Dot, // both Dot and Powerup are of type Entity
	Powerup,
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

	void setTex(const wchar_t);

	friend bool operator==(const Entity& e1, const Entity& e2)
	{
		return &e1 == &e2;
	}

	friend bool operator!=(const Entity& e1, const Entity& e2)
	{
		return !(e1 == e2);
	}

	Entity(int, int, wchar_t, EntityType);
	Entity(wchar_t, EntityType);
	virtual ~Entity() {};
};