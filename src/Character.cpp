#include "Character.h"
#include "EntityMgr.h"
#include "PacMan.h"

void Character::setSpeed(float newSpeed)
{
	if (newSpeed > 0)
		m_speed = newSpeed;
}

void Character::moveUp()
{
	performMove(m_y, true, &Character::isYBorderColliding);
}

void Character::moveDown()
{
	performMove(m_y, false, &Character::isYBorderColliding);
}

void Character::moveLeft()
{
	performMove(m_x, true, &Character::isXBorderColliding);
}

void Character::moveRight()
{
	performMove(m_x, false, &Character::isXBorderColliding);
}

void Character::performMove(float& coord, bool upOrLeft, bool(Character::*func)())
{
	float delta{ m_speed * Engine::getDeltaTime() };
	if (upOrLeft)
		delta *= -1; // -1 so += becomes -= and -= becomes +=

	// func is either isXBorderColliding or isYBorderColliding
	if (!(this->*func)()) coord += delta;
	if (((this->*func)()) || gPacMan.getWindowMgr().tryGetEntMgr()->checkViolationFor(*this)) coord -= delta;
}

bool Character::isXBorderColliding()
{
	return m_x < 0 ||
		static_cast<unsigned int>(m_x) >= gScreenWidth;
}

bool Character::isYBorderColliding()
{
	return m_y < 0 ||
		static_cast<unsigned int>(m_y) >= gPlayableSpaceHeight;
}

float Character::getSpeed() { return m_speed; }

bool Character::isDead() const
{
	return m_isDead;
}

Character::Character(int x, int y, wchar_t texture)
	: Entity{ x, y, texture, EntityType::Character }
{}

Character::Character(int x, int y, wchar_t texture, EntityType enttype)
	: Entity{ x, y, texture, enttype}
{}

Character::Character(wchar_t texture)
	: Entity{ texture, EntityType::Character }
{}