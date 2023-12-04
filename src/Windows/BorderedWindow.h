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
	void renderHorizontalBars();
	void renderVertBars();
	void renderText(unsigned int offsetX, unsigned int offsetY, const std::wstring& str);
public:
	void render() override;

	unsigned int getWidth();
	unsigned int getHeight();
	int getOffsetX();
	int getOffsetY();

	static unsigned int calcOffsetCenteredText(unsigned int, unsigned int, unsigned int);

	BorderedWindow(unsigned int width, unsigned int height, int offsetX, int offsetY);
};