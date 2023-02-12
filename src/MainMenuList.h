#pragma once
#include "Engine/MenuList.h"

class MainMenuList : public MenuList
{
public:
	void handleInput() override;
	void render();

	MainMenuList(std::initializer_list<MenuButton>);
};