#pragma once
#include <string>
#include "../Engine/DynamicMenuList.h"
#include "../MapFile.h"

using MapFileVector = std::vector<MapFile>;

class MapMenuList : public DynamicMenuList
{
private:
	MapFileVector m_mapFiles{};
	// maybe temporary
	std::vector<std::wstring> m_mapFileNames{};

public:
	MapMenuList();
	std::wstring removeExtension(const wchar_t*);
	void readMapFiles();
	void handleInput() override;
	void render();

	const MapFileVector& getMapFiles();
	const std::vector<std::wstring>& getMapFileNames();
};