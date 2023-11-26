#include "Entity.h"

unsigned int Entity::interpretXY(float x, float y)
{
	return static_cast<unsigned int>(x +
		static_cast<unsigned int>(y) * gScreenWidth);
}

unsigned int Entity::getPos() const
{
	return interpretXY(m_x, m_y);
}

float Entity::getVirtualX() const
{
	return m_x;
}

float Entity::getVirtualY() const
{
	return m_y;
}

wchar_t Entity::getTex() const { return m_texture; }
EntityType Entity::getEntType() const { return m_entitytype; }
void Entity::setTex(const wchar_t newTex) { m_texture = newTex; }
void Entity::teleportTo(unsigned int x, unsigned int y)
{
	m_x = static_cast<float>(x);
	m_y = static_cast<float>(y);
}

Entity::Entity(int x, int y, wchar_t texture, EntityType enttype)
{
	m_x = static_cast<float>(x);
	m_y = static_cast<float>(y);
	m_texture = texture;
	m_entitytype = enttype;
}

Entity::Entity(wchar_t texture, EntityType enttype)
{
	m_texture = texture;
	m_entitytype = enttype;
}