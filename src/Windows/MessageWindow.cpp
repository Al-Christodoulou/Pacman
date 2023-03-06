#include <Windows.h>
#include <cmath>
#include "MessageWindow.h"
#include "../PacMan.h"

void MessageWindow::render()
{
	// render in the middle of the screen
	const unsigned int topLeftPosRow{ gScreenHeight / 2 - m_height / 2 };
	const unsigned int topLeftPosColumn{ gScreenWidth / 2 - m_width / 2 };

	const unsigned int topRightPosColumn{ topLeftPosColumn + m_width };
	const unsigned int bottomLeftPosRow{ topLeftPosRow + m_height };

	// gPacMan.fillscreen() isn't being called here since a message window
	// doesn't take up the entire screen

	// the top left, top right, buttom left, bottom right textures
	gPacMan.sendDataf(L'\u2554', topLeftPosRow, topLeftPosColumn);
	gPacMan.sendDataf(L'\u2557', topLeftPosRow, topRightPosColumn);
	gPacMan.sendDataf(L'\u255A', bottomLeftPosRow, topLeftPosColumn);
	gPacMan.sendDataf(L'\u255D', bottomLeftPosRow, topRightPosColumn);
	// the horizontal bars
	renderHorizontalCont(topLeftPosRow, topLeftPosColumn, bottomLeftPosRow);
	// the vertical bars
	renderVertCont(topLeftPosRow, topLeftPosColumn, topRightPosColumn);
	// all text rendering
	renderText(topLeftPosRow, topLeftPosColumn, topRightPosColumn, bottomLeftPosRow);
}

void MessageWindow::renderHorizontalCont(unsigned int topLeftPosRow, unsigned int topLeftPosColumn, unsigned int bottomLeftPosRow)
{
	for (unsigned int i{ 1 }; i < m_width; i++)
	{
		gPacMan.sendDataf(L'\u2550', topLeftPosRow, topLeftPosColumn + i);
		gPacMan.sendDataf(L'\u2550', bottomLeftPosRow, topLeftPosColumn + i);

		// make the insides of the message window empty
		for (unsigned int j{ 1 }; j < m_height; j++)
			gPacMan.sendDataf(L' ', topLeftPosRow + j, topLeftPosColumn + i);
	}
}

void MessageWindow::renderVertCont(unsigned int topLeftPosRow, unsigned int topLeftPosColumn, unsigned int topRightPosColumn)
{
	for (unsigned int i{ 1 }; i < m_height; i++)
	{
		gPacMan.sendDataf(L'\u2551', topLeftPosRow + i, topLeftPosColumn);
		gPacMan.sendDataf(L'\u2551', topLeftPosRow + i, topRightPosColumn);
	}
}

void MessageWindow::renderText(unsigned int topLeftPosRow, unsigned int topLeftPosColumn, unsigned int topRightPosColumn, unsigned int bottomLeftPosRow)
{
	// a lambda for wrapping up offset calculations. calculate the middle point between
	// 2 columns, then adjust it for the text length (...-txtSize/2) so you get the
	// right offset for the 1st character of the string you want to show on the window,
	// so in the end it's oriented in the middle
	auto calcOffset{ [](unsigned int col1, unsigned int col2, unsigned int txtSize) {
		return (col1 + col2) / 2 - txtSize / 2;
	} };

	// the distance (+1) of the title and the OK button from the top & bottom borders
	constexpr unsigned int textBorderDist{ 2 };

	// the title, rendered 3 (textBorderDist) rows after the top border
	gPacMan.sendDataf(m_title.data(), m_title.size(), topLeftPosRow + textBorderDist, calcOffset(topLeftPosColumn, topRightPosColumn, m_title.size()));

	unsigned int linesNeeded{ static_cast<unsigned int>(
		std::ceil(static_cast<float>(m_msg.size()) / m_width)
	)};

	for (unsigned int i{ 0 }; i < linesNeeded; i++)
	{
		const unsigned int textSize{
			i == linesNeeded - 1 ?
			m_msg.size() - (linesNeeded - 1) * (m_width - 1):
			m_width - 1
		};
		const unsigned int textRow{ topLeftPosRow + textBorderDist * 2 + i };
		const unsigned int textColumn{ calcOffset(topLeftPosColumn, topRightPosColumn, textSize) };

		gPacMan.sendDataf(m_msg.data() + (m_width - 1) * i, textSize, textRow, textColumn);
	}

	// the "OK" text, rendered 3 (textBorderDist) rows before the bottom border
	gPacMan.sendDataf(L"> OK <", 6, bottomLeftPosRow - textBorderDist, calcOffset(topLeftPosColumn, topRightPosColumn, 6));
}

void MessageWindow::runLogic()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_state_terminate = true;
}

MessageWindow::MessageWindow(unsigned int width, unsigned int height, std::wstring_view title, std::wstring_view msg)
	: m_width{ width }, m_height{ height }, m_title{ title }, m_msg{ msg }, Window{ WindowType::Other }
{}