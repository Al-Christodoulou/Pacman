#pragma once
#include <string_view>
#include "../Engine/Window.h"
#include "../WindowTypes.h"

// a simple Message Window with an optional "OK" button. it renders
// on the middle of the screen
class MessageWindow : public Window<WindowType>
{
private:
	// m_textBorderDist is the distance (+1) of the title
	// and the OK button from the top & bottom borders
	const unsigned int m_width, m_height, m_textBorderDist;
	const int m_offsetX, m_offsetY;
	std::wstring m_title, m_msg;
	const bool m_hasOKButton;

public:
	void render() override;
	// render the horizontal content of the window (the horizontal
	// bars and the empty space inside it)
	void renderHorizontalCont(unsigned int, unsigned int, unsigned int);
	void renderVertCont(unsigned int, unsigned int, unsigned int);
	void renderText(unsigned int, unsigned int, unsigned int, unsigned int);
	void runLogic() override;

	void setTitle(const std::wstring&);
	void setMessage(const std::wstring&);
	const std::wstring& getTitle();
	const std::wstring& getMessage();

	static unsigned int calcOffsetCenteredText(unsigned int, unsigned int, unsigned int);

	// width, height, title, message text, text border distance, has OK button
	MessageWindow(unsigned int, unsigned int, const std::wstring&, const std::wstring&,
				unsigned int = 2, int offsetX = 0, int offsetY = 0, bool = true);
};