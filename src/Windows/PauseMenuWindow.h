#pragma once
#include <string>
#include "../Engine/CustomInt.h"
#include "BorderedWindow.h"

class PauseMenuWindow : public BorderedWindow
{
private:
	enum MenuOptions : unsigned int
	{
		Resume_game = 0,
		Options,
		Exit,
		max_num_options
	};

	// TODO: MSVC 2019 has a bug where static constexpr wchar_t MenuOptions can't evaluate to a
	// constant, i'm making this const inline for now
	static const inline wchar_t MenuOptions[MenuOptions::max_num_options][12]{
		L"Resume game",
		L"Options",
		L"Exit"
	};
	static constexpr unsigned int MenuOptionsLens[]{
		11, 7, 4
	};
	unsigned int m_menuOptionsOffsetsX[MenuOptions::max_num_options];
	CustomInt m_menuIndex{ 0, MenuOptions::max_num_options - 1 };

public:
	void render() override;
	void runLogic() override;

	PauseMenuWindow();
};

