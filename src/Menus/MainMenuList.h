#pragma once
#include "../Engine/ConstMenuList.h"

class MainMenuList : public ConstMenuList<2>
{
private:
	// a keyword train
	static constexpr unsigned int textHeight{ 3 };
	static constexpr unsigned int startBtnWidth{ 23 };
	static constexpr unsigned int exitBtnWidth{ 17 };

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
	void handleInput() override;
	void render();
	void renderCursor(unsigned int, unsigned int);

	MainMenuList(const MenuButtonArray_t<2>&);
};