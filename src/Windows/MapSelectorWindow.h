#pragma once
#include "../Engine/Window.h"
#include "../WindowTypes.h"
#include "../MenuLists/MapMenuList.h"

class MapSelectorWindow : public Window<WindowType>
{
private:
	MapMenuList m_mapMenuList{};

public:
	void render() override;
	void runLogic() override;

	MapSelectorWindow();
};