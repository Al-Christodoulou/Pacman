#pragma once
#include <string>
#include <filesystem>
#include "../Engine/BaseMenuList.h"
#include "../MapFile.h"

using MapFileVector = std::vector<MapFile>;

class MapMenuList : public BaseMenuList
{
private:
	MapFileVector m_mapFiles{};
	// maybe temporary
	std::vector<std::wstring> m_mapFileNames{};

public:
	MapMenuList();
	std::wstring removeExtension(const wchar_t*);
	void readMapFiles();
	void insertIfMapFile(const std::filesystem::path&);
	unsigned int getMaxIndex() override;
	bool mapHasPlayerSpawn(const MapFile& map);
	void handleInput() override;
	void render();

	const MapFileVector& getMapFiles();
	const std::vector<std::wstring>& getMapFileNames();
};