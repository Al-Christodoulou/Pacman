#pragma once
#include "../Engine/BaseMenuList.h"

class MainMenuList : public BaseMenuList
{
private:
	// a keyword train
	static constexpr inline unsigned int textHeight{ 3 };
	static constexpr inline unsigned int startBtnWidth{ 23 };
	static constexpr inline unsigned int exitBtnWidth{ 17 };

	static constexpr inline wchar_t startButton[textHeight][startBtnWidth]{
		L"/-- ---   ^   /--/ ---",
		L"\\-\\  |   /-\\  |-/   | ",
		L"--/  |  /   \\ |  \\  | "
	};

	static constexpr inline wchar_t exitButton[textHeight][exitBtnWidth]{
		L"/--  \\/  --- ---",
		L"|--  /\\   |   | ",
		L"\\-- /  \\ ---  | "
	};

	// this can't be marked constexpr for some reason,
	// "expression did not evaluate to a constant"
	static const inline wchar_t cursor[textHeight][textHeight]{
		L"\\",
		L" >",
		L"/"
	};

public:
	unsigned int getMaxIndex() override;
	void handleInput() override;
	void render();
	void renderCursor(unsigned int, unsigned int);

	MainMenuList();
};