#pragma once
#include "Engine.h"

class PacMan
{
private:
	wchar_t* m_screen{ new wchar_t[gScreenTotalPxs] };
	Engine m_engine{};

public:
	void fillscreen(wchar_t);
	// data, size of data, offset
	void sendData(wchar_t*, unsigned int, unsigned int);
	void sendData(wchar_t, unsigned int); // one character
	//void swprintf_s(size_t, const wchar_t*, ...);

	void run();
};