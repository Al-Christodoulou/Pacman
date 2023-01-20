#pragma once
#include "Character.h"

class Ghost : public Character
{
public:
	void think() override;
	Ghost(int, int);
};