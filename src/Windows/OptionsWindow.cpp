#include "OptionsWindow.h"
#include "../PacMan.h"

#define ToFontSize(A) static_cast<FontSize>(static_cast<unsigned int>(A))

void OptionsWindow::runLogic()
{
	if (gPacMan.isKeyTapped(VK_ESCAPE))
		m_state_terminate = true;

	if (gPacMan.isKeyTapped(L'A'))
		--m_fontIndex;
	if (gPacMan.isKeyTapped(L'D'))
		++m_fontIndex;
}

void OptionsWindow::render()
{
	BorderedWindow::render();

	// render title
	renderTextCentered(-1, L"Options");

	static constexpr unsigned int offsetRow{ gScreenHeight / 2 };
	static constexpr unsigned int offsetCol{ (gScreenWidth - BarSize + 2) / 2 };

	for (unsigned int i{ 0 }; i < BarSize; i++)
	{
		gPacMan.sendDataf(BarSlideTex, offsetRow, offsetCol + i);
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		gPacMan.sendDataf(BarTex, offsetRow - 1 + i, offsetCol + 1 + m_fontIndex * BarOptionSpace);
	}

	// offsets for the "Font size:" text
	static constexpr unsigned int fontSizeTextRow{ offsetRow + 3 };
	static constexpr unsigned int fontSizeTextCol{ offsetCol - 1 };
	static constexpr unsigned int fontSizeTextLen{ 11 };
	gPacMan.sendDataf(L"Font size:", fontSizeTextLen, fontSizeTextRow, fontSizeTextCol);

	// offset for the actual setting text after the "..size:" text
	static constexpr unsigned int fontSizeSettingTextCol{ fontSizeTextCol + fontSizeTextLen };
	static constexpr unsigned int fontSizeSettingLen{ 12 };

	std::wstring fontSettingText{ fontSizeSettingLen };
	fontSettingText.reserve(fontSizeSettingLen);

	switch (ToFontSize(m_fontIndex))
	{
	case FontSize::Small:
		fontSettingText = L"small";
		gPacMan.setFontSize(FontSize::Small);
		break;
	case FontSize::Medium:
		fontSettingText = L"medium";
		gPacMan.setFontSize(FontSize::Medium);
		break;
	case FontSize::Large:
		fontSettingText = L"large";
		gPacMan.setFontSize(FontSize::Large);
		break;
	case FontSize::Extra_Large:
		fontSettingText = L"extra large";
		gPacMan.setFontSize(FontSize::Extra_Large);
		break;
	}
	gPacMan.sendDataf(fontSettingText.c_str(), fontSettingText.length(), fontSizeTextRow, fontSizeSettingTextCol);
}

OptionsWindow::OptionsWindow()
	: BorderedWindow(27, 10),
	  m_fontIndex{
		0,
		static_cast<unsigned int>(FontSize::max_number_font_sizes) - 1,
		static_cast<int>(gPacMan.getFontSize())
	  }
{
	m_saveFile.open(SaveFileOpenMode::Write);
}

OptionsWindow::~OptionsWindow()
{
	if (m_saveFile.canWrite())
		m_saveFile.writeFontSize(ToFontSize(m_fontIndex));
}