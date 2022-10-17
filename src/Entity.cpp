#include "Entity.h"

unsigned int Entity::getPos() const
{
	return static_cast<unsigned int>(m_y +
		static_cast<unsigned int>(m_y) * gScreenWidth);
}

wchar_t Entity::getTex() const { return m_texture; }

Entity::Entity(int x, int y, wchar_t texture)
{
	m_x = static_cast<float>(x);
	m_y = static_cast<float>(y);
	m_texture = texture;
}

Entity::Entity(wchar_t texture)
{
	m_texture = texture;
}