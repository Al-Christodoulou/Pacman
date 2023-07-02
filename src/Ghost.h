#pragma once
#include "Character.h"

class Ghost : public Character
{
public:
	void think() override;
	void touch(Entity&) override;
	Ghost(int, int);
};