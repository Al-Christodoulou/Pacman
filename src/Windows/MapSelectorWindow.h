#pragma once
#include <string>
#include <filesystem>
#include "../WindowTypes.h"
#include "../Engine/Window.h"
#include "../Engine/CustomInt.h"
#include "../Constants.h"

// forward declare the class to avoid more includes
class MapFile;

class MapSelectorWindow : public Window<WindowType>
{
private:
	// the first line from where the maps will get shown from
	static constexpr unsigned int BaseLine{ 5 };

	// it's BaseLine * 2 so we cut off both the top 5 and the bottom
	// 5 lines from the calculation
	static constexpr size_t MaxShownMaps{
		(gScreenHeight - BaseLine * 2) / 2
	};

	std::vector<MapFile> m_mapFiles{};
	// maybe temporary
	std::vector<std::wstring> m_mapFileNames{};

	CustomInt m_menuIndex{ 0, 0 };
	// this is used to emulate "scrolling" behavior
	unsigned int m_firstShownMapIndex{ 0 };
public:
	void render() override;
	void runLogic() override;

	void renderMapList() const;
	void renderScrollBar() const;

	std::wstring removeExtension(const std::wstring&);
	void readMapFiles();
	void insertIfMapFile(const std::filesystem::path&);
	bool mapHasPlayerSpawn(const MapFile& map);

	MapSelectorWindow();
};