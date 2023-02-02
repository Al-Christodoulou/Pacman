#include <stdarg.h>
#include "PacMan.h"
#include "EntityMgr.h"
#include "Character.h"
#include "Player.h"
#include "WanderingLouse.h"
#include "Ghost.h"
#include "Random.h"

PacMan gPacMan{};

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
	// start the game with the game window for now
	m_windowMgr.pushGameWindow();

	while (true)
	{
		//Sleep(20);
		Engine::tick();
		m_windowMgr.update();
		m_engine.renderScreen(m_screen);
	}
}

const WindowMgr& PacMan::getWindowMgr() { return m_windowMgr; }