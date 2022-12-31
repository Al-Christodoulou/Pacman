#pragma once
#include "Entity.h"

// an abstract class that defines a movable entity with thinking logic
class Character : public Entity
{
private:
	float m_speed{ 20.0f }; // the speed of the entity in pixels per second

public:
	enum class MoveAction
	{
		UP, DOWN, LEFT, RIGHT,
		max_actions
	};

// TODO: this is ugly
private:
	MoveAction m_lastAction{ MoveAction::UP };
public:

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool willEntCollide(const Entity&, bool onX);
	bool isXBorderColliding();
	bool isYBorderColliding();

	float getSpeed();
	MoveAction getLastAction() const;

	virtual void think() = 0;

	friend bool operator==(const Character& c1, const Character& c2)
	{
		return &c1 == &c2;
	}

	friend bool operator!=(const Character& c1, const Character& c2)
	{
		return !(c1 == c2);
	}

	Character(int, int, wchar_t);
	Character(wchar_t);
};