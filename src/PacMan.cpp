#include "PacMan.h"
#include "EntityMgr.h"
#include "Character.h"
#include "Player.h"
#include "WanderingLouse.h"
#include "Ghost.h"
#include "Random.h"

void PacMan::fillscreen(wchar_t data)
{
	for (int i{ 0 }; i < gScreenTotalPxs; i++)
		m_screen[i] = data;
}

void PacMan::sendData(wchar_t* data, unsigned int size, unsigned int offset)
{
	// if the data's gonna go out of bounds, don't do anything
	if (offset + size > gScreenTotalPxs)
		return;

	for (unsigned int i{ 0 }; i < size; i++)
		m_screen[i + offset] = data[i];
}

void PacMan::sendData(wchar_t c, unsigned int offset)
{
	if (offset <= gScreenTotalPxs)
		m_screen[offset] = c;
}

/*void PacMan::swprintf_s(size_t _BufferCount, const wchar_t* _Format, ...)
{
	va_list args;
	va_start(args, _Format);
	::swprintf_s(m_screen, _BufferCount, _Format, )
}*/

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

	//std::vector<Ghost*> tempGhostVec{};
	/*for (int i{0}; i < 100; i++)
	{
		for (int j{ 0 }; j < 50; j++)
			tempGhostVec.push_back(gEntMgr.createGhost(1 + i, 1 + j));
	}*/
	WanderingLouse* louse{ gEntMgr.createEntSpecification<WanderingLouse>
		((gScreenWidth / 2) - 3, (gScreenHeight / 2) - 5)
	};
	Ghost* ghost{ gEntMgr.createEntSpecification<Ghost>
		((gScreenWidth / 2) - 5, (gScreenHeight - 2))
	};

	while (true)
	{
		//Sleep(20);
		Engine::tick();
		fillscreen(L' ');
		renderAllEntities();

		player->think();
		louse->think();
		ghost->think();
		//for (Ghost* ghost : tempGhostVec)
		//	ghost->think();

		swprintf_s(m_screen, 40, L"X: %f, Y: %f",
			player->getVirtualX(), player->getVirtualY()
		);
		swprintf_s(m_screen + gScreenWidth, 30, L"DT: %f", m_engine.getDeltaTime());

		m_engine.renderScreen(m_screen);
	}
}