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
	for (unsigned int i{ 0 }; i < m_entitymgr.getArraySize(); i++)
	{
		const Entity* curEnt{ m_entitymgr.getEntity(i) };
		if (curEnt)
			m_screen[curEnt->getPos()] = curEnt->getTex();
	}
}

void PacMan::run()
{
	Player* player{ m_entitymgr.createPlayer(gScreenWidth / 2, gScreenHeight / 2, 0x555) };
	for (int i{ 0 }; i < 50; i++)
		m_entitymgr.createEnt(Random::get(0, gScreenWidth), Random::get(0, gScreenHeight), L'#');

	while (true)
	{
		Engine::tick();
		fillscreen(L' ');
		renderAllEntities();
		for (unsigned int i{ 0 }; i < m_entitymgr.getArraySize(); i++)
		{
			if (!player->willEntCollide(*m_entitymgr.getEntity(i), false))
			{
				if (GetAsyncKeyState(L'W') & 0x8000)
					player->moveUp();
				if (GetAsyncKeyState(L'S') & 0x8000)
					player->moveDown();
			}
			else if (!player->willEntCollide(*m_entitymgr.getEntity(i), true))
			{
				if (GetAsyncKeyState(L'A') & 0x8000)
					player->moveLeft();
				if (GetAsyncKeyState(L'D') & 0x8000)
					player->moveRight();
			}
		}
		swprintf_s(m_screen, 50, L"X: %f, Y: %f",
			player->getVirtualX(), player->getVirtualY()
		);
		//swprintf_s(m_screen, 30, L"DT: %f", m_engine.getDeltaTime());

		m_engine.renderScreen(m_screen);
	}
}