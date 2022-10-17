#include "PacMan.h"
#include "Character.h"
#include "Player.h"

void PacMan::fillscreen(wchar_t data)
{
	for (int i{ 0 }; i < gScreenTotalPxs; i++)
		m_screen[i] = data;
}

void PacMan::renderAllEntities()
{
	for (unsigned int i{ 0 }; i < m_entitymgr.getArraySize(); i++)
	{
		const Entity* curEnt{ m_entitymgr.getEntity(i) };
		if (curEnt)
			m_screen[i] = curEnt->getTex();
	}
}

void PacMan::run()
{
	//Player* player{ new Player{static_cast<wchar_t>(0x555)} };
	while (true)
	{
		Engine::tick();
		fillscreen(L' ');
		renderAllEntities();

		m_engine.renderScreen(m_screen);
	}
}