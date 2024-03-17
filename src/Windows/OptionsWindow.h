#pragma once
#include "../Engine/Window.h"
#include "../WindowTypes.h"
#include "../Engine/CustomInt.h"
#include "../Engine/EngineStructs.h"
#include "../SaveFile.h"
#include "BorderedWindow.h"

class OptionsWindow : public BorderedWindow
{
private:
	static constexpr wchar_t BarSlideTex{ L'\u2550' };
	static constexpr wchar_t BarTex{ L'\u2551' };
	static constexpr unsigned int BarSize{ 18 };
	static constexpr unsigned int BarOptionSpace{
		(BarSize - 2) / (static_cast<unsigned int>(FontSize::max_number_font_sizes) - 1)
	};

	CustomInt m_fontIndex;
	SaveFile m_saveFile{};
public:
	void runLogic() override;
	void render() override;

	OptionsWindow();
	~OptionsWindow() override;
};