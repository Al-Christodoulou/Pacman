#include "Character.h"

void Character::moveUp()
{
	if (!isYBorderColliding()) m_y -= m_speed * Engine::getDeltaTime();
	if (isYBorderColliding()) m_y += m_speed * Engine::getDeltaTime();
}

void Character::moveDown()
{
	if (!isYBorderColliding()) m_y += m_speed * Engine::getDeltaTime();
	if (isYBorderColliding()) m_y -= m_speed * Engine::getDeltaTime();
}

void Character::moveLeft()
{
	if (!isXBorderColliding()) m_x -= m_speed * Engine::getDeltaTime();
	if (isXBorderColliding()) m_x += m_speed * Engine::getDeltaTime();
}

void Character::moveRight()
{
	if (!isXBorderColliding()) m_x += m_speed * Engine::getDeltaTime();
	if (isXBorderColliding()) m_x -= m_speed * Engine::getDeltaTime();
}

bool Character::willEntCollide(const Entity& other, bool onX)
{
	unsigned int predictedPos{};
	const float delta{ m_speed * Engine::getDeltaTime() };
	if (onX)
		predictedPos = interpretXY(m_x + delta, m_y);
	else
		predictedPos = interpretXY(m_x, m_y + delta - 1.0f);
	if (other.getPos() == predictedPos)
		return true;
	return false;
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