#pragma once
#include <vector>
#include <initializer_list>
#include "MenuButton.h"

class MenuList
{
private:
	const std::vector<MenuButton> m_buttons;
	unsigned int m_selectedIndex{ 0 };

public:
	MenuList(std::initializer_list<MenuButton> buttons)
		: m_buttons{ buttons }
	{}

	virtual void handleInput() = 0;
};