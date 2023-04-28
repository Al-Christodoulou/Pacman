#pragma once
#include "../Engine/Window.h"
#include "../EntityMgr.h"
#include "../Player.h"
#include "../WindowTypes.h"
#include "../MapFile.h"

class GameWindow : public Window<WindowType>
{
private:
	const MapFile m_mapFile;
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
	// the timer used to reset a round or a game
	float m_resetTimestamp{ 0.0f };

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

	// the num of lives parameter's used for new game rounds
	void initEntities(unsigned int plNumOfLives = 3);
	void renderAllEntities();
	void restartRound();

	const EntityMgr& getEntMgr() const;

	GameWindow(const MapFile&);
};