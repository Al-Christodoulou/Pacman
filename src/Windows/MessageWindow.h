#pragma once
#include <string_view>
#include "../Engine/Window.h"
#include "../WindowTypes.h"

// a simple Message Window with an "OK" button. it renders
// on the middle of the screen
class MessageWindow : public Window<WindowType>
{
private:
	unsigned int m_width, m_height;
	std::wstring_view m_title, m_msg;

public:
	void render() override;
	// render the horizontal content of the window (the horizontal
	// bars and the empty space inside it)
	void renderHorizontalCont(unsigned int, unsigned int, unsigned int);
	void renderVertCont(unsigned int, unsigned int, unsigned int);
	void renderText(unsigned int, unsigned int, unsigned int, unsigned int);
	void runLogic() override;

	// width, height, title, message text
	MessageWindow(unsigned int, unsigned int, std::wstring_view, std::wstring_view);
};