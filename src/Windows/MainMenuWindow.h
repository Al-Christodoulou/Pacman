#pragma once
#include "../Engine/Window.h"
#include "../WindowTypes.h"

class MainMenuWindow : public Window<WindowType>
{
public:
	void render() override;
	void runLogic() override;

	MainMenuWindow()
		: Window(WindowType::Other)
	{}
};