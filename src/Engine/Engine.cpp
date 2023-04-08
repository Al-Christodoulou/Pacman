#include <Windows.h>
#include "../Engine/Engine.h"

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

void Engine::updateKeyStates()
{
	// TODO: if someone passes a lowercase letter to isKeyTapped
	// or isKeyHeld, there may be a problem, since the virtual
	// key codes for letters are all capitalized
	for (int i{ 0 }; i < 255; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			if (m_keyStates.m_isHeld[i])
				m_keyStates.m_isTapped[i] = false;
			else
				m_keyStates.m_isTapped[i] = true;
			m_keyStates.m_isHeld[i] = true;
		}
		else
			m_keyStates.m_isHeld[i] = false;
	}
}

bool Engine::isKeyTapped(wchar_t key)
{
	return m_keyStates.m_isTapped[static_cast<int>(key)];
}

bool Engine::isKeyHeld(wchar_t key)
{
	return m_keyStates.m_isHeld[static_cast<int>(key)];
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