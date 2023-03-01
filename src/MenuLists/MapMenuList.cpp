#include "MapMenuList.h"
#include "../Windows/GameWindow.h"

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

void MapMenuList::handleInput()
{
	if (GetAsyncKeyState(L'W') & 0x1)
		goUp();
	else if (GetAsyncKeyState(L'S') & 0x1)
		goDown();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000 && m_mapFiles.size() > 0)
		gPacMan.getWindowMgr().pushAnyWindow<GameWindow>(m_mapFiles[getIndex()]);
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
			gPacMan.sendDataf(L'>', row, column - 3);
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