#pragma once
#include <string>
#include "../Engine/Window.h"
#include "../WindowTypes.h"

// a window with a visible border around it, something
// like:
//
// +==============+
// |  Text here!  |
// +==============+
//
// the class contains all the necessary methods for
// adding text inside the window. by default it is
// rendered on the middle of the screen, this can
// be changed via m_offsetX and offsetY
class BorderedWindow : public Window<WindowType>
{
private:
	unsigned int m_width, m_height;
	int m_offsetX, m_offsetY;

	unsigned int m_topLeftPosRow;
	unsigned int m_topLeftPosColumn;
	unsigned int m_topRightPosColumn;
	unsigned int m_bottomLeftPosRow;

	// render the horizontal content of the window (the horizontal
	// bars and the empty space inside it)
	void renderHorizontalBars() const;
	void renderVertBars() const;

protected:
	void renderText(int offsetX, int offsetY, const wchar_t* str, unsigned int str_len, bool = false) const;
	void renderText(int offsetX, int offsetY, const std::wstring& str, bool = false) const;
	unsigned int renderTextCentered(int offsetY, const wchar_t* str, unsigned int str_len, bool = false) const;
	unsigned int renderTextCentered(int offsetY, const std::wstring& str, bool = false) const;
public:
	void render() override;

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	int getOffsetX() const;
	int getOffsetY() const;

	static unsigned int calcOffsetCenteredText(unsigned int, unsigned int, unsigned int);

	BorderedWindow(unsigned int width, unsigned int height, int offsetX = 0, int offsetY = 0);
};