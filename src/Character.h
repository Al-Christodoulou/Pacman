#pragma once
#include <vector>
#include "EntityMgrTypedefs.h"

// an abstract class that defines a movable entity with thinking logic
class Character : public Entity
{
private:
	float m_speed{ 20.0f }; // the speed of the entity in pixels per second

protected:
	void setSpeed(float);
	bool m_isDead{ false };

public:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	// just to reduce copy-pasted code
	void performMove(float&, bool, bool(Character::*)());

	bool isXBorderColliding();
	bool isYBorderColliding();

	float getSpeed();
	bool isDead() const;
	void setDead(bool);

	virtual void think() = 0;
	virtual void touch(const ConstEntityArrayIterator&) = 0;
	// called after all the entities have been created
	virtual void init() = 0;

	Character(int, int, wchar_t, EntityType);
	Character(wchar_t, EntityType);
};