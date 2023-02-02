#pragma once
#include "Engine.h"
#include "WindowMgr.h"

class PacMan
{
private:
	wchar_t* m_screen{ new wchar_t[gScreenTotalPxs] };
	Engine m_engine{};
	WindowMgr m_windowMgr{};

public:
	void fillscreen(wchar_t);
	// data, size of data, offset
	void sendData(wchar_t*, unsigned int, unsigned int);
	void sendData(wchar_t, unsigned int); // one character
	//void swprintf_s(size_t, const wchar_t*, ...);

	void run();
	const WindowMgr& getWindowMgr();

	// no copying or moving is allowed
	PacMan(const PacMan&) = delete;
	PacMan(PacMan&&) = delete;
	PacMan() = default;
};

// maybe bad
extern PacMan gPacMan;