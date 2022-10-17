#pragma once
#include "Engine.h"
#include "EntityMgr.h"

class PacMan
{
private:
	wchar_t* m_screen{ new wchar_t[gScreenTotalPxs] };
	Engine m_engine{};
	EntityMgr m_entitymgr{};

public:
	void fillscreen(wchar_t data);
	void renderAllEntities();
	void run();
};