#include <Windows.h>
#include <cmath>
#include "MessageWindow.h"
#include "../PacMan.h"

void MessageWindow::render()
{
	// render in the middle of the screen
	const unsigned int topLeftPosRow{ gScreenHeight / 2 - m_height / 2 + m_offsetY };
	const unsigned int topLeftPosColumn{ gScreenWidth / 2 - m_width / 2 + m_offsetX };

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

// calculate the middle point between 2 columns, then adjust it for the text length
// (...-txtSize/2), so you get the right offset for the 1st character of the string
// you want to show on the window, so in the end it's oriented in the middle
unsigned int MessageWindow::calcOffsetCenteredText(unsigned int col1, unsigned int col2, unsigned int txtSize)
{
	return (col1 + col2) / 2 - txtSize / 2;
}

void MessageWindow::renderText(unsigned int topLeftPosRow, unsigned int topLeftPosColumn,
							unsigned int topRightPosColumn, unsigned int bottomLeftPosRow)
{
	// the title, rendered 3 (textBorderDist) rows after the top border
	gPacMan.sendDataf(m_title.data(), m_title.size(), topLeftPosRow + m_textBorderDist,
					calcOffsetCenteredText(topLeftPosColumn, topRightPosColumn, m_title.size())
	);

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
		const unsigned int textRow{ topLeftPosRow + m_textBorderDist + i };
		// it's topLeftPosColumn + 1 so it goes one block right from the border. i don't understand
		// why this isn't an issue with topRightPosColumn, maybe it's textSize limiting it?
		const unsigned int textColumn{ calcOffsetCenteredText(topLeftPosColumn + 1, topRightPosColumn, textSize) };

		gPacMan.sendDataf(m_msg.data() + (m_width - 1) * i, textSize, textRow, textColumn);
	}

	if (m_hasOKButton)
	{
		// the "OK" text, rendered 3 (textBorderDist) rows before the bottom border
		gPacMan.sendDataf(L"> OK <", 6, bottomLeftPosRow - m_textBorderDist,
						calcOffsetCenteredText(topLeftPosColumn, topRightPosColumn, 6)
		);
	}
}

void MessageWindow::runLogic()
{
	if (gPacMan.isKeyTapped(VK_RETURN))
		m_state_terminate = true;
}

void MessageWindow::setTitle(const std::wstring& title)
{
	m_title = title;
}

void MessageWindow::setMessage(const std::wstring& msg)
{
	m_msg = msg;
}

const std::wstring& MessageWindow::getTitle()
{
	return m_title;
}

const std::wstring& MessageWindow::getMessage()
{
	return m_msg;
}

MessageWindow::MessageWindow(unsigned int width, unsigned int height,
							const std::wstring& title, const std::wstring& msg,
							unsigned int textBorderDist, int offsetX, int offsetY,
							bool hasOKButton)
	: m_width{ width }, m_height{ height }, m_title{ title },
	m_msg{ msg }, Window{ WindowType::Other }, m_textBorderDist{ textBorderDist },
	m_offsetX{ offsetX }, m_offsetY{ offsetY }, m_hasOKButton{ hasOKButton }
{}