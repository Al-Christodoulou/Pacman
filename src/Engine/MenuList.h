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
	const unsigned int m_maxIndex;
	unsigned int m_selectedIndex{ 0 };

public:
	MenuList(std::initializer_list<MenuButton> buttons)
		: m_buttons{ buttons }, m_maxIndex{ buttons.size() }
	{}

	void goUp()
	{
		if (m_selectedIndex == 0)
			m_selectedIndex = m_maxIndex;
		else
			--m_selectedIndex;
	}

	void goDown()
	{
		if (m_selectedIndex == m_maxIndex)
			m_selectedIndex = 0;
		else
			++m_selectedIndex;
	}

	virtual void handleInput() = 0;
};