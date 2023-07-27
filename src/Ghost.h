#pragma once
#include "Character.h"

class Ghost : public Character
{
public:
	void think() override;
	void touch(const ConstEntityArrayIterator&) override;
	Ghost(int, int, float);
};