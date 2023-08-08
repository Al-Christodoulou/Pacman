#pragma once
#include "Character.h"

class Ghost : public Character
{
private:
	bool m_isVulnerable{ false };
	const Player* m_targetPlayer{};

public:
	void think() override;
	void touch(const ConstEntityArrayIterator&) override;
	void init() override;

	Ghost(int, int, float);
};