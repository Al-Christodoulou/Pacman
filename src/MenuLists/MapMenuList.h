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
	std::vector<std::string> m_mapFileNames{};

public:
	MapMenuList();
	std::wstring removeExtension(const wchar_t*);
	std::string convertToString(const std::wstring&);
	void readMapFiles();
};