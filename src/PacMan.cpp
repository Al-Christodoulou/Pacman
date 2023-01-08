#include "PacMan.h"
#include "Character.h"
#include "Player.h"
#include "Random.h"

void PacMan::fillscreen(wchar_t data)
{
	for (int i{ 0 }; i < gScreenTotalPxs; i++)
		m_screen[i] = data;
}

void PacMan::renderAllEntities()
{
	for (unsigned int i{ 0 }; i < gEntMgr.getArraySize(); i++)
	{
		const Entity* curEnt{ gEntMgr.getEntity(i) };
		if (curEnt)
			m_screen[curEnt->getPos()] = curEnt->getTex();
	}
}

void PacMan::run()
{
	Player* player{ gEntMgr.createPlayer(gScreenWidth / 2, gScreenHeight / 2, 0x555) };
	for (int i{ 0 }; i < 50; i++)
		gEntMgr.createEnt(Random::get(0, gScreenWidth), Random::get(0, gScreenHeight), L'#');
	gEntMgr.createEnt((gScreenWidth / 2), (gScreenHeight / 2) - 4, L'#');
	gEntMgr.createEnt((gScreenWidth / 2) - 1, (gScreenHeight / 2) - 4, L'#');
	gEntMgr.createEnt((gScreenWidth / 2) + 1, (gScreenHeight / 2) - 4, L'#');
	
	gEntMgr.createEnt((gScreenWidth / 2), (gScreenHeight / 2) - 3, L'#');
	gEntMgr.createEnt((gScreenWidth / 2) - 1, (gScreenHeight / 2) - 3, L'#');
	gEntMgr.createEnt((gScreenWidth / 2) + 1, (gScreenHeight / 2) - 3, L'#');

	while (true)
	{
		Engine::tick();
		fillscreen(L' ');
		renderAllEntities();

		player->think();

		swprintf_s(m_screen, 40, L"X: %f, Y: %f",
			player->getVirtualX(), player->getVirtualY()
		);
		//swprintf_s(m_screen, 30, L"DT: %f", m_engine.getDeltaTime());

		m_engine.renderScreen(m_screen);
	}
}