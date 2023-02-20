#pragma once
#include "../Engine/Window.h"
#include "../WindowTypes.h"
#include "../Menus/MainMenuList.h"

class MainMenuWindow : public Window<WindowType>
{
private:
	MainMenuList m_mainMenuList;

public:
	void render() override;
	void runLogic() override;

	MainMenuList constructMainMenuList();
	MainMenuWindow();
};