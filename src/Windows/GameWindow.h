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
	enum class GameState
	{
		FreezeTime = 0,
		Playing,
		PlayerDead,
		max_game_states
	} m_gameState{ GameState::FreezeTime };

	EntityMgr m_entMgr{};
	Player* m_player{ nullptr };

	// the amount of time passed since this game started. this is used
	// for all game events to avoid issues when pausing the game
	float m_gameTime{ 0.0f };

	static constexpr float cFreezeTime{ 4.0f };
	static constexpr unsigned int cSecondsTextOffset{
		gScreenWidth * gPlayableSpaceHeight +
		gScreenWidth + gScreenWidth / 4
	};
	static constexpr unsigned int cPlayerLivesTextOffset{
		gScreenWidth * gPlayableSpaceHeight +
		gScreenWidth + 6
	};

public:
	void render() override;
	void runLogic() override;

	void initEntities(const MapFile&);
	void renderAllEntities();

	const EntityMgr& getEntMgr() const;

	GameWindow(const MapFile&);
};