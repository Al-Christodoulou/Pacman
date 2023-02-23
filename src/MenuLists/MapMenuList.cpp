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
	constexpr wchar_t mapFolderName[]{ L"/Win32 Debug/maps" };
	std::wstring mapFolder{ std::filesystem::current_path().c_str() };
	mapFolder.append(mapFolderName);

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
	if (GetAsyncKeyState(L'W' & 0x1))
		goUp();
	if (GetAsyncKeyState(L'S' & 0x1))
		goDown();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_buttons[getIndex()].onPress();
}

void MapMenuList::render()
{
	constexpr unsigned int baseLine{ 5 };

	unsigned int i{ 0 };
	for (const std::wstring& mapName : m_mapFileNames)
	{
		const unsigned int column{ gScreenWidth / 2 - mapName.size() / 2 };
		// if the file was successfully read, it can be rendered to the menu
		if (m_mapFiles[i])
			gPacMan.sendDataf(mapName.c_str(), mapName.size(), baseLine + i * 2, column);

		// render the cursor
		if (getIndex() == i)
			gPacMan.sendDataf(L'>', baseLine, column - 3);
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