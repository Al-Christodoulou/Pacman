#pragma once
#include "Engine.h"

class PacMan
{
private:
	wchar_t* m_screen{ new wchar_t[gScreenTotalPxs] };
	Engine m_engine{};

public:
	void fillscreen(wchar_t data);
	void renderAllEntities();
	void run();
};