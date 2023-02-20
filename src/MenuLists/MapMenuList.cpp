#include <filesystem>
#include "MapMenuList.h"

MapMenuList::MapMenuList()
	: DynamicMenuList{}
{
	readMapFiles();
}

void MapMenuList::readMapFiles()
{
	constexpr wchar_t mapFolder[]{ L"./maps" };

	// if this folder doesn't exist, there's no maps
	if (!std::filesystem::exists(mapFolder))
		return;

	// for each file in the maps folder, create a MapFile object and insert
	// it inside m_mapFiles
	for (const auto& entry : std::filesystem::directory_iterator(mapFolder))
		m_mapFiles.emplace_back(entry.path().c_str());
}