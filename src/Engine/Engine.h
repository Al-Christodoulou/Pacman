#pragma once
#include <chrono>
#include <Windows.h>
#include "../Constants.h"
#include "Log.h"
#include "EngineStructs.h"

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
	CONSOLE_FONT_INFOEX m_fontInfo{};
	FontSize m_fontSize{ FontSize::Large };

	void setupFont();
	void setupWindowInfo();
public:
	static Log Log;

	static void tick();
	static float getDeltaTime();
	void updateKeyState(int);
	void setFontSize(FontSize);
	FontSize getFontSize() const;
	bool isKeyTapped(wchar_t);
	bool isKeyHeld(wchar_t);
	void renderScreen(wchar_t*);
	Engine();
};