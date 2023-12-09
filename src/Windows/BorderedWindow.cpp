#include "../PacMan.h"
#include "BorderedWindow.h"

void BorderedWindow::renderHorizontalBars()
{
	for (unsigned int i{ 1 }; i < m_width; i++)
	{
		gPacMan.sendDataf(L'\u2550', m_topLeftPosRow, m_topLeftPosColumn + i);
		gPacMan.sendDataf(L'\u2550', m_bottomLeftPosRow, m_topLeftPosColumn + i);

		// make the insides of the message window empty
		for (unsigned int j{ 1 }; j < m_height; j++)
			gPacMan.sendDataf(L' ', m_topLeftPosRow + j, m_topLeftPosColumn + i);
	}
}

void BorderedWindow::renderVertBars()
{
	for (unsigned int i{ 1 }; i < m_height; i++)
	{
		gPacMan.sendDataf(L'\u2551', m_topLeftPosRow + i, m_topLeftPosColumn);
		gPacMan.sendDataf(L'\u2551', m_topLeftPosRow + i, m_topRightPosColumn);
	}
}

// startFromBottom means that offsetY will start from the bottom border of the
// window instead of the top border
void BorderedWindow::renderText(int offsetX, int offsetY,
								const wchar_t* str, unsigned int str_len, bool startFromBottom)
{
	const unsigned int startRow{ startFromBottom ? m_bottomLeftPosRow - 1 : m_topLeftPosRow + 1 };
	gPacMan.sendDataf(str, str_len, startRow + offsetY, m_topLeftPosColumn + 1 + offsetX);
}

void BorderedWindow::renderText(int offsetX, int offsetY,
								const std::wstring& str, bool startFromBottom)
{
	renderText(offsetX, offsetY, str.c_str(), str.size(), startFromBottom);
}

// both renderTextCentered return the offsetX that was calculated by this method
unsigned int BorderedWindow::renderTextCentered(int offsetY, const wchar_t* str,
												unsigned int str_len, bool startFromBottom)
{
	const unsigned int startRow{ startFromBottom ? m_bottomLeftPosRow - 1 : m_topLeftPosRow + 1 };
	unsigned int column{ calcOffsetCenteredText(m_topLeftPosColumn + 1, m_topRightPosColumn, str_len) };
	gPacMan.sendDataf(str, str_len, startRow + offsetY, column);

	// make the column index an offset relative to the window
	return column - m_topLeftPosColumn - 1;
}

unsigned int BorderedWindow::renderTextCentered(int offsetY, const std::wstring& str,
												bool startFromBottom)
{
	return renderTextCentered(offsetY, str.c_str(), str.size(), startFromBottom);
}

void BorderedWindow::render()
{
	// gPacMan.fillscreen() isn't being called here since a message window
	// doesn't take up the entire screen
	// the top left, top right, buttom left, bottom right textures
	gPacMan.sendDataf(L'\u2554', m_topLeftPosRow, m_topLeftPosColumn);
	gPacMan.sendDataf(L'\u2557', m_topLeftPosRow, m_topRightPosColumn);
	gPacMan.sendDataf(L'\u255A', m_bottomLeftPosRow, m_topLeftPosColumn);
	gPacMan.sendDataf(L'\u255D', m_bottomLeftPosRow, m_topRightPosColumn);
	// the horizontal bars
	renderHorizontalBars();
	// the vertical bars
	renderVertBars();

	// text rendering will happen in any derived class via renderText & renderTextCentered
}

unsigned int BorderedWindow::getWidth()
{
	return m_width;
}

unsigned int BorderedWindow::getHeight()
{
	return m_height;
}

int BorderedWindow::getOffsetX()
{
	return m_offsetX;
}

int BorderedWindow::getOffsetY()
{
	return m_offsetY;
}


// calculate the middle point between 2 columns, then adjust it for the text length
// (...-txtSize/2), so you get the right offset for the 1st character of the string
// you want to show on the window, so in the end it's oriented in the middle
unsigned int BorderedWindow::calcOffsetCenteredText(unsigned int col1, unsigned int col2, unsigned int txtSize)
{
	return (col1 + col2 - txtSize) / 2;
}

BorderedWindow::BorderedWindow(unsigned int width, unsigned int height, int offsetX, int offsetY)
	: Window{ WindowType::Other }, m_width { width }, m_height{ height },
	m_offsetX{ offsetX }, m_offsetY{ offsetY }
{
	m_topLeftPosRow = gScreenHeight / 2 - m_height / 2 + m_offsetY;
	m_topLeftPosColumn = gScreenWidth / 2 - m_width / 2 + m_offsetX;
	m_topRightPosColumn = m_topLeftPosColumn + m_width;
	m_bottomLeftPosRow = m_topLeftPosRow + m_height;
}