#include <filesystem>
#include "MapMenuList.h"

MapMenuList::MapMenuList()
	: DynamicMenuList{}
{
	readMapFiles();
}

std::wstring MapMenuList::removeExtension(const wchar_t* inPath)
{
	std::wstring path{ inPath };
	return path.substr(0, path.find_last_of(L'.'));
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
	{
		m_mapFiles.emplace_back(entry.path().c_str());
		std::wstring mapName{ removeExtension(entry.path().filename().c_str()) };
		m_mapFileNames.push_back(mapName);
	}
}

void MapMenuList::handleInput()
{
	if (GetAsyncKeyState(L'W' & 0x8000))
		goUp();
	if (GetAsyncKeyState(L'S' & 0x8000))
		goDown();
}

const MapFileVector& MapMenuList::getMapFiles()
{
	return m_mapFiles;
}

const std::vector<std::wstring>& MapMenuList::getMapFileNames()
{
	return m_mapFileNames;
}