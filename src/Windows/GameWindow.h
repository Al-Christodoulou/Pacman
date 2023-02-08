#pragma once
#include "../Engine/Window.h"
#include "../EntityMgr.h"
#include "../Player.h"
#include "../WindowTypes.h"

class GameWindow : public Window<WindowType>
{
private:
	EntityMgr m_entMgr{};
	Player* m_player{ nullptr };

public:
	void render() override;
	void runLogic() override;

	void initEntities();
	void renderAllEntities();

	const EntityMgr& getEntMgr() const;

	GameWindow();
};