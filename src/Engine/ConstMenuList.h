#pragma once
#include "BaseMenuList.h"
#include <array>

template<unsigned int Size>
using MenuButtonArray_t = std::array<MenuButton, Size>;

template <unsigned int Size>
class ConstMenuList : public BaseMenuList
{
protected:
	const MenuButtonArray_t<Size> m_buttons;

public:
	ConstMenuList(const MenuButtonArray_t<Size>& buttons)
		: m_buttons{ buttons }
	{}

	void goUp() { BaseMenuList::goUp(Size - 1); }
	void goDown() { BaseMenuList::goDown(Size - 1); }
};