#pragma once
#include "../Engine/Window.h"
#include "../WindowTypes.h"
#include "../Engine/CustomInt.h"

class MainMenuWindow : public Window<WindowType>
{
private:
	// a keyword train
	static constexpr inline unsigned int textHeight{ 3 };
	static constexpr inline unsigned int startBtnWidth{ 23 };
	static constexpr inline unsigned int optionsButtonWidth{ 27 };
	static constexpr inline unsigned int exitBtnWidth{ 17 };

	static constexpr inline wchar_t startButton[textHeight][startBtnWidth]{
		L"/-- ---   ^   /--/ ---",
		L"\\-\\  |   /-\\  |-/   | ",
		L"--/  |  /   \\ |  \\  | "
	};

	static constexpr inline wchar_t optionsButton[textHeight][optionsButtonWidth]{
		L"/-\\ /-\\ --- | /-\\ |\\ | /--",
		L"| | |-/  |  | | | | \\| \\-|",
		L"\\-/ |    |  | \\-/ |  | --/",
	};

	static constexpr inline wchar_t exitButton[textHeight][exitBtnWidth]{
		L"/--  \\/  --- ---",
		L"|--  /\\   |   | ",
		L"\\-- /  \\ ---  | "
	};

	// this can't be marked constexpr for some reason,
	// "expression did not evaluate to a constant"
	static const inline wchar_t leftCursor[textHeight][textHeight]{
		L"\\",
		L" >",
		L"/"
	};

	static const inline wchar_t rightCursor[textHeight][textHeight]{
		L" /",
		L"< ",
		L" \\"
	};

	CustomInt m_menuIndex{ 0, 2 };
public:
	void render() override;
	void renderList();
	void renderListCursor(unsigned int baseLine, unsigned int lineButtonDelta);
	void runLogic() override;

	MainMenuWindow();
};