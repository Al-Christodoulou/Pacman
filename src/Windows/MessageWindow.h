#pragma once
#include <string_view>
#include "../Engine/Window.h"
#include "BorderedWindow.h"
#include "../WindowTypes.h"

// a simple Message Window with an optional "OK" button. it renders
// on the middle of the screen
class MessageWindow : public BorderedWindow
{
private:
	// m_textBorderDist is the distance (+1) of the title
	// and the OK button from the top & bottom borders
	unsigned int m_textBorderDist;
	std::wstring m_title, m_msg;
	const bool m_hasOKButton;
public:
	void render() override;
	void runLogic() override;

	void setTitle(const std::wstring&);
	void setMessage(const std::wstring&);
	const std::wstring& getTitle();
	const std::wstring& getMessage();

	// width, height, offX, offY, title, message text, text border distance, has OK button
	MessageWindow(unsigned int, unsigned int, int offsetX, int offsetY,
		const std::wstring&, const std::wstring&, unsigned int = 2, bool = true);
};