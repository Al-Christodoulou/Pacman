#pragma once
#include "../Engine/Window.h"
#include "../EntityMgr.h"
#include "../Player.h"
#include "../WindowTypes.h"

// forward declare to avoid includes
class MapFile;

class GameWindow : public Window<WindowType>
{
private:
	EntityMgr m_entMgr{};
	Player* m_player{ nullptr };

public:
	void render() override;
	void runLogic() override;

	void initEntities(const MapFile&);
	void renderAllEntities();

	const EntityMgr& getEntMgr() const;

	GameWindow(const MapFile&);
};