#pragma once
#include "Engine/MenuList.h"

class MainMenuList : public MenuList
{
public:
	void handleInput() override;

	MainMenuList(std::initializer_list<MenuButton>);
};