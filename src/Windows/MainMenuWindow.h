#pragma once
#include "../Window.h"

class MainMenuWindow : public Window
{
public:
	void render() override;
	void runLogic() override;

	MainMenuWindow()
		: Window(WindowType::Other)
	{}
};