#pragma once
#include "../Engine/DynamicMenuList.h"
#include "../MapFile.h"

using MapFileVector = std::vector<MapFile>;

class MapMenuList : public DynamicMenuList
{
private:
	MapFileVector m_mapFiles{};

public:
	MapMenuList();
	void readMapFiles();
};