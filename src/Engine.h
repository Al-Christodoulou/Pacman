#pragma once
#include <chrono>
#include <Windows.h>

constexpr unsigned int gScreenWidth{ 120 };
constexpr unsigned int gScreenHeight{ 40 };
constexpr unsigned int gScreenTotalPxs{ gScreenWidth * gScreenHeight };

using timep_t = std::chrono::system_clock::time_point;

class Engine
{
private:
	static timep_t sTimeNow;
	static float sDeltaTime;
	HANDLE m_hConsole{ CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0) };

	void setupFont();
	void setupWindowInfo();
public:
	static void tick();
	static float getDeltaTime();
	void renderScreen(wchar_t*);
	Engine();
};