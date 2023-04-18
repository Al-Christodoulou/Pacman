#pragma once
#include <string>
#include <filesystem>
#include "../WindowTypes.h"
#include "../Engine/Window.h"
#include "../Engine/CustomInt.h"

// forward declare the class to avoid more includes
class MapFile;

class MapSelectorWindow : public Window<WindowType>
{
private:
	std::vector<MapFile> m_mapFiles{};
	// maybe temporary
	std::vector<std::wstring> m_mapFileNames{};

	CustomInt m_menuIndex{ 0, 0 };
public:
	void render() override;
	void runLogic() override;

	std::wstring removeExtension(const std::wstring&);
	void readMapFiles();
	void insertIfMapFile(const std::filesystem::path&);
	bool mapHasPlayerSpawn(const MapFile& map);

	MapSelectorWindow();
};