#pragma once
#include "Entity.h"

// an abstract class that defines a movable entity with thinking logic
class Character : public Entity
{
private:
	float m_speed{ 20.0f }; // the speed of the entity in pixels per second

public:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool willEntCollide(const Entity&, bool onX);
	bool isXBorderColliding();
	bool isYBorderColliding();

	virtual void think() = 0;

	Character(int, int, wchar_t);
	Character(wchar_t);
};