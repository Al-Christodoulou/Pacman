#pragma once
#include <vector>
#include <initializer_list>
#include "MenuButton.h"

// an abstract class that holds menu buttons, with a selected index
// that increases/decreases based on keyboard input
class MenuList
{
protected:
	const std::vector<MenuButton> m_buttons;
	unsigned int m_selectedIndex{ 0 };

public:
	MenuList(std::initializer_list<MenuButton> buttons)
		: m_buttons{ buttons }
	{}

	virtual void handleInput() = 0;
};