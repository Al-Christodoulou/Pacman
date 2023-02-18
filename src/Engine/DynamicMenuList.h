#pragma once
#include "BaseMenuList.h"
#include <vector>

class DynamicMenuList : public BaseMenuList
{
protected:
	std::vector<MenuButton> m_buttons;
	unsigned int m_maxIndex{};

public:
	DynamicMenuList(const std::initializer_list<MenuButton>& buttons)
		: m_buttons{ buttons }
	{}

	void addButton(MenuButton&& button) { m_buttons.emplace_back(button); }
	void removeBackButton() { m_buttons.pop_back(); }
};