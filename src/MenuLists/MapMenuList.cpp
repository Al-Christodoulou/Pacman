#include "MapMenuList.h"
#include "../Windows/GameWindow.h"
#include "../Windows/MessageWindow.h"

MapMenuList::MapMenuList()
	: BaseMenuList{}
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
	constexpr wchar_t mapFolderName[]{ L"/Win32 Debug/maps" };
	std::wstring mapFolder{ std::filesystem::current_path().c_str() };
	mapFolder.append(mapFolderName);

	// if this folder doesn't exist, there's no maps
	if (!std::filesystem::exists(mapFolder))
		return;

	// for each file in the maps folder, check it's validity and update
	// m_mapFiles & m_mapFileNames if it's a valid map
	for (const auto& entry : std::filesystem::directory_iterator(mapFolder))
		insertIfMapFile(entry.path());
}

void MapMenuList::insertIfMapFile(const std::filesystem::path& mapPath)
{
	// if this path doesn't refer to a file, don't do anything
	if (!std::filesystem::is_regular_file(mapPath))
		return;

	MapFile mapFile{ mapPath.c_str() };
	if (!mapFile)
		return;

	m_mapFiles.push_back(mapFile);
	m_mapFileNames.push_back(removeExtension(mapPath.filename().c_str()));
}

unsigned int MapMenuList::getMaxIndex()
{
	return m_mapFiles.size() - 1;
}

bool MapMenuList::mapHasPlayerSpawn(const MapFile& map)
{
	for (const std::string& line : map.getData())
		for (char c : line)
			if (c == 'p')
				return true;
	return false;
}

void MapMenuList::handleInput()
{
	if (gPacMan.isKeyTapped(L'W'))
		goUp();
	else if (gPacMan.isKeyTapped(L'S'))
		goDown();

	if (gPacMan.isKeyTapped(VK_RETURN) && m_mapFiles.size() > 0)
	{
		// used for the "sv" (string_view) conversions after the quotes in
		// pushAnyWindow<MessageWindow> below
		using namespace std::string_view_literals;
		
		if (mapHasPlayerSpawn(m_mapFiles[getIndex()]))
			gPacMan.getWindowMgr().pushAnyWindow<GameWindow>(m_mapFiles[getIndex()]);
		else
			gPacMan.getWindowMgr().pushAnyWindow<MessageWindow>(31, 10, L"Error"sv, L"No player spawn point in map file."sv);
	}
}

void MapMenuList::render()
{
	constexpr unsigned int baseLine{ 5 };

	unsigned int i{ 0 };
	for (const std::wstring& mapName : m_mapFileNames)
	{
		const unsigned int row{ baseLine + i * 2 };
		const unsigned int column{ gScreenWidth / 2 - mapName.size() / 2 };
		gPacMan.sendDataf(mapName.c_str(), mapName.size(), row, column);

		// render the cursor
		if (getIndex() == i)
		{
			gPacMan.sendDataf(L'>', row, column - 3);
			gPacMan.sendDataf(L'<', row, column + mapName.size() + 3 - 1);
		}
		i++;
	}
}

const MapFileVector& MapMenuList::getMapFiles()
{
	return m_mapFiles;
}

const std::vector<std::wstring>& MapMenuList::getMapFileNames()
{
	return m_mapFileNames;
}