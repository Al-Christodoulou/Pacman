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
	//for (int i{ 0 }; i < 50; i++)
	//	m_entitymgr.createEnt(Random::get(0, gScreenWidth), Random::get(0, gScreenHeight), L'#');
	m_entitymgr.createEnt((gScreenWidth / 2), (gScreenHeight / 2) - 4, L'#');

	while (true)
	{
		Engine::tick();
		fillscreen(L' ');
		renderAllEntities();

		if (GetAsyncKeyState(L'W') & 0x8000)
		{
			for (unsigned int i{ 0 }; i < m_entitymgr.getArraySize(); i++)
			{
				if (m_entitymgr.getEntity(i) == player ||
					!player->willEntCollide(*m_entitymgr.getEntity(i), false))
				{
					//swprintf_s(m_screen + gScreenWidth * 3, 30, L"BANG!");
					//const float delta{ player->getSpeed() * Engine::getDeltaTime() };
					//unsigned int predictedPos{ Entity::interpretXY(player->getVirtualX(), player->getVirtualY() + delta + 1.0f) };
					//m_screen[predictedPos] = L'@';
					player->moveUp();
					break;
				}
			}
		}

		if (GetAsyncKeyState(L'A') & 0x8000)
		{
			for (unsigned int i{ 0 }; i < m_entitymgr.getArraySize(); i++)
			{
				if (!player->willEntCollide(*m_entitymgr.getEntity(i), true) &&
					m_entitymgr.getEntity(i) != player)
				{
					player->moveLeft();
					break;
				}
			}
		}

		swprintf_s(m_screen, 50, L"X: %f, Y: %f",
			player->getVirtualX(), player->getVirtualY()
		);
		//swprintf_s(m_screen, 30, L"DT: %f", m_engine.getDeltaTime());

		m_engine.renderScreen(m_screen);
	}
}