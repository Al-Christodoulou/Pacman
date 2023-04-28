#pragma once
#include "Character.h"

class Ghost : public Character
{
public:
	void think() override;
	void touch(Character&) override;
	Ghost(int, int);
};