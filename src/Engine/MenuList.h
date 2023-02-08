#pragma once
#include <vector>
#include <initializer_list>
#include "MenuButton.h"

class MenuList
{
private:
	typedef void (*MenuListVoidFunc)();

	const std::vector<MenuButton> m_buttons;
	unsigned int m_selectedIndex{ 0 };
	const MenuListVoidFunc m_renderFunc{ nullptr };

public:
	MenuList(MenuListVoidFunc renderFunc, std::initializer_list<MenuButton> buttons)
		: m_renderFunc{ renderFunc }, m_buttons { buttons }
	{}
};