#include <Windows.h>
#include "Engine.h"
#include "../SaveFile.h"

timep_t Engine::sTimeNow{ std::chrono::system_clock::now() };
float Engine::sDeltaTime{ 0.0f };
Log Engine::Log = Log;

void Engine::setupFont()
{
	m_fontInfo.cbSize = sizeof(m_fontInfo);
	m_fontInfo.nFont = 0;

	SaveFile sf{};
	sf.open(SaveFileOpenMode::Read);
	if (sf.canRead())
		setFontSize(sf.readFontSize());
	else
		setFontSize(FontSize::Large);

	m_fontInfo.FontFamily = FF_DONTCARE;
	m_fontInfo.FontWeight = FF_DONTCARE;
	wcscpy_s(m_fontInfo.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(m_hConsole, false, &m_fontInfo);
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

void Engine::updateKeyState(int index)
{
	// TODO: if someone passes a lowercase letter to isKeyTapped
	// or isKeyHeld, this won't work, since the virtual key codes
	// for letters are all the capitalized ASCII letters
	if (GetKeyState(index) & 0x8000)
	{
		m_keyStates.m_isTapped[index] = false;
		if (!m_keyStates.m_isHeld[index])
		{
			m_keyStates.m_isHeld[index] = true;
			m_keyStates.m_isTapped[index] = true;
		}
	}
	else
	{
		m_keyStates.m_isTapped[index] = false;
		m_keyStates.m_isHeld[index] = false;
	}
}

void Engine::setFontSize(FontSize fontsize)
{
	switch (fontsize)
	{
	case FontSize::Small:
		m_fontInfo.dwFontSize.X = 10;
		m_fontInfo.dwFontSize.Y = 14;
		m_fontSize = FontSize::Small;
		break;
	case FontSize::Medium:
		m_fontInfo.dwFontSize.X = 12;
		m_fontInfo.dwFontSize.Y = 16;
		m_fontSize = FontSize::Medium;
		break;
	case FontSize::Large:
		m_fontInfo.dwFontSize.X = 14;
		m_fontInfo.dwFontSize.Y = 18;
		m_fontSize = FontSize::Large;
		break;
	case FontSize::Extra_Large:
		m_fontInfo.dwFontSize.X = 16;
		m_fontInfo.dwFontSize.Y = 20;
		m_fontSize = FontSize::Extra_Large;
		break;
	default: // shouldn't happen unless a save file's corrupted
		m_fontInfo.dwFontSize.X = 14;
		m_fontInfo.dwFontSize.Y = 18;
		m_fontSize = FontSize::Large;
		break;
	}
	SetCurrentConsoleFontEx(m_hConsole, false, &m_fontInfo);
}

FontSize Engine::getFontSize() const
{
	return m_fontSize;
}

bool Engine::isKeyTapped(wchar_t key)
{
	int index{ static_cast<int>(key) };
	updateKeyState(index);
	return m_keyStates.m_isTapped[index];
}

bool Engine::isKeyHeld(wchar_t key)
{
	int index{ static_cast<int>(key) };
	updateKeyState(index);
	return m_keyStates.m_isHeld[index];
}

void Engine::renderScreen(wchar_t* data)
{
	DWORD dwBytesWritten{};
	// the last char of the array is the end
	data[gScreenTotalPxs - 1] = L'\0';
	WriteConsoleOutputCharacter(m_hConsole, data, gScreenTotalPxs, { 0, 0 }, &dwBytesWritten);
}

Engine::Engine()
{
	setupFont();
	setupWindowInfo();
}