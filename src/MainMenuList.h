#pragma once
#include "Engine/ConstMenuList.h"

class MainMenuList : public ConstMenuList<2>
{
public:
	void handleInput() override;
	void render();

	MainMenuList(const MenuButtonArray_t<2>&);
};