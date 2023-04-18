#include <stdarg.h>
#include "PacMan.h"
#include "EntityMgr.h"
#include "Character.h"
#include "Player.h"
#include "WanderingLouse.h"
#include "Ghost.h"
#include "Windows/MainMenuWindow.h"

PacMan gPacMan{};

void PacMan::fillscreen(wchar_t data)
{
	for (int i{ 0 }; i < gScreenTotalPxs; i++)
		m_screen[i] = data;
}

void PacMan::sendData(const wchar_t* data, unsigned int size, unsigned int offset)
{
	// if the data's gonna go out of bounds, don't do anything
	if (offset + size > gScreenTotalPxs)
		return;

	for (unsigned int i{ 0 }; i < size; i++)
		m_screen[i + offset] = data[i];
}

void PacMan::sendDataf(const wchar_t* data, unsigned int size, unsigned int row, unsigned int column)
{
	sendData(data, size, row * gScreenWidth + column);
}

void PacMan::sendDataf(const wchar_t data, unsigned int row, unsigned int column)
{
	sendData(data, row * gScreenWidth + column);
}

void PacMan::sendData(const wchar_t c, unsigned int offset)
{
	if (offset <= gScreenTotalPxs)
		m_screen[offset] = c;
}

// a wrapper around swprintf_s (with the v in front of swprint.. meaning
// it takes a va_list as a parameter)
void PacMan::swprintf_s(size_t _BufferCount, const wchar_t* _Format, ...)
{
	va_list args;
	va_start(args, _Format);
	::vswprintf_s(m_screen, _BufferCount, _Format, args);
	va_end(args);
}

// same as above, but with an offset
void PacMan::swprintf_s(unsigned int offset, size_t _BufferCount, const wchar_t* _Format, ...)
{
	va_list args;
	va_start(args, _Format);
	::vswprintf_s(m_screen + offset, _BufferCount, _Format, args);
	va_end(args);
}

bool PacMan::isKeyTapped(wchar_t key)
{
	return m_engine.isKeyTapped(key);
}

bool PacMan::isKeyHeld(wchar_t key)
{
	return m_engine.isKeyHeld(key);
}

void PacMan::run()
{
	m_windowMgr.pushAnyWindow<MainMenuWindow>();

	while (true)
	{
		//Sleep(20);
		Engine::tick();
		if (!m_windowMgr.update())
			break;
		m_engine.renderScreen(m_screen);
	}
}

WindowMgr& PacMan::getWindowMgr() { return m_windowMgr; }