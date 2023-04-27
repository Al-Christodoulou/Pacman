#pragma once
#include <chrono>
#include <Windows.h>
#include "../Constants.h"

using timep_t = std::chrono::system_clock::time_point;

class Engine
{
private:
	static timep_t sTimeNow;
	static float sDeltaTime;
	HANDLE m_hConsole{ CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0) };
	struct KeyStates
	{
		bool m_isTapped[255]{};
		bool m_isHeld[255]{};
	} m_keyStates;

	void setupFont();
	void setupWindowInfo();
public:
	static void tick();
	static float getDeltaTime();
	void updateKeyState(int);
	bool isKeyTapped(wchar_t);
	bool isKeyHeld(wchar_t);
	void renderScreen(wchar_t*);
	Engine();
};