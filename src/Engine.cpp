#include <Windows.h>
#include "Engine.h"

timep_t Engine::sTimeNow{ std::chrono::system_clock::now() };
float Engine::sDeltaTime{ 0.0f };

void Engine::setupFont()
{
	CONSOLE_FONT_INFOEX fontInfo{};
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.dwFontSize.X = 12;
	fontInfo.dwFontSize.Y = 16;
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FF_DONTCARE;
	wcscpy_s(fontInfo.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(m_hConsole, false, &fontInfo);
}

void Engine::setupWindowInfo()
{
	COORD buffer{ static_cast<short>(gScreenWidth), static_cast<short>(gScreenHeight) };
	SetConsoleScreenBufferSize(m_hConsole, buffer);
	SMALL_RECT rect{ 0, 0, static_cast<short>(gScreenWidth - 1), static_cast<short>(gScreenHeight - 1) };
	SetConsoleWindowInfo(m_hConsole, true, &rect);
	SetConsoleTitle(L"PacMan!");
	SetConsoleActiveScreenBuffer(m_hConsole);
}

void Engine::tick()
{
	std::chrono::duration<float> deltaTime{ std::chrono::system_clock::now() - sTimeNow };
	sDeltaTime = deltaTime.count();
	sTimeNow = std::chrono::system_clock::now();
}

float Engine::getDeltaTime()
{
	return sDeltaTime;
}

void Engine::renderScreen(wchar_t* data)
{
	DWORD dwBytesWritten{};
	// the last char of the array is the end
	data[gScreenTotalPxs] = '\0';
	WriteConsoleOutputCharacter(m_hConsole, data, gScreenTotalPxs, { 0, 0 }, &dwBytesWritten);
}

Engine::Engine()
{
	setupFont();
	setupWindowInfo();
}