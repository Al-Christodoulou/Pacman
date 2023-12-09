#include <Windows.h>
#include <cmath>
#include "MessageWindow.h"
#include "../PacMan.h"

void MessageWindow::render()
{
	BorderedWindow::render();

	// all the text rendering happens below
	renderTextCentered(m_textBorderDist, m_title);

	unsigned int linesNeeded{ static_cast<unsigned int>(
		std::ceil(static_cast<float>(m_msg.size()) / getWidth())
	)};

	for (unsigned int i{ 0 }; i < linesNeeded; i++)
	{
		const unsigned int textSize{
			i == linesNeeded - 1 ?
			m_msg.size() - (linesNeeded - 1) * (getWidth() - 1):
			getWidth() - 1
		};
		renderTextCentered(m_textBorderDist + i, m_msg.substr((getWidth() - 1) * i, textSize));
	}

	if (m_hasOKButton)
	{
		// the "OK" text, rendered 3 (textBorderDist) rows before the bottom border
		renderTextCentered(-static_cast<int>(m_textBorderDist), L"> OK <", 7, true);
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
							int offsetX, int offsetY,
							const std::wstring& title, const std::wstring& msg,
							unsigned int textBorderDist, bool hasOKButton)
	: BorderedWindow{ width, height, offsetX, offsetY }, m_title{ title },
	m_msg{ msg }, m_textBorderDist{ textBorderDist }, m_hasOKButton{ hasOKButton }
{}