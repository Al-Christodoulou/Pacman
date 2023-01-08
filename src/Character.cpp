#include "Character.h"
#include "EntityMgr.h"

void Character::moveUp()
{
	const float delta{ m_speed * Engine::getDeltaTime() };
	if (!isYBorderColliding()) m_y -= delta;
	if (isYBorderColliding() || gEntMgr.checkViolationFor(*this)) m_y += delta;
}

void Character::moveDown()
{
	const float delta{ m_speed * Engine::getDeltaTime() };
	if (!isYBorderColliding()) m_y += delta;
	if (isYBorderColliding() || gEntMgr.checkViolationFor(*this)) m_y -= delta;
}

void Character::moveLeft()
{
	const float delta{ m_speed * Engine::getDeltaTime() };
	if (!isXBorderColliding()) m_x -= delta;
	if (isXBorderColliding() || gEntMgr.checkViolationFor(*this)) m_x += delta;
}

void Character::moveRight()
{
	const float delta{ m_speed * Engine::getDeltaTime() };
	if (!isXBorderColliding()) m_x += m_speed * Engine::getDeltaTime();
	if (isXBorderColliding() || gEntMgr.checkViolationFor(*this)) m_x -= m_speed * Engine::getDeltaTime();
}

bool Character::isXBorderColliding()
{
	return static_cast<unsigned int>(m_x) == 0 ||
		static_cast<unsigned int>(m_x) == gScreenWidth;
}

bool Character::isYBorderColliding()
{
	return static_cast<unsigned int>(m_y) == 0 ||
		static_cast<unsigned int>(m_y) == gScreenHeight;
}

float Character::getSpeed() { return m_speed; }

Character::Character(int x, int y, wchar_t texture)
	: Entity{ x, y, texture, EntityType::Character }
{}

Character::Character(wchar_t texture)
	: Entity{ texture, EntityType::Character }
{}