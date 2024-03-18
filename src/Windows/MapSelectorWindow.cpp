// fixes collision with the "min" macro of Windows.h
#define NOMINMAX

#include <cstdlib>
#include "MapSelectorWindow.h"
#include "GameWindow.h"
#include "MessageWindow.h"
#include "MainMenuWindow.h"
#include "../MapFile.h"
#include "../PacMan.h"

void MapSelectorWindow::render()
{
	gPacMan.fillscreen(L' ');

	const size_t maxShownMaps{ std::min(m_mapFileNames.size(), MaxShownMaps) };
	const size_t iGuard{ std::min(m_mapFileNames.size(), m_firstShownMapIndex + maxShownMaps) };
	for (size_t i = m_firstShownMapIndex; i < iGuard; i++)
	{
		const std::wstring& mapName{ m_mapFileNames[i] };
		const unsigned int row{ BaseLine + (i - m_firstShownMapIndex) * 2 };
		const unsigned int column{ gScreenWidth / 2 - mapName.size() / 2 };
		gPacMan.sendDataf(mapName.c_str(), mapName.size(), row, column);

		// render the cursor
		if (static_cast<unsigned int>(m_menuIndex) == i)
		{
			gPacMan.sendDataf(L'>', row, column - 3);
			gPacMan.sendDataf(L'<', row, column + mapName.size() + 3 - 1);
		}
	}
}

void MapSelectorWindow::runLogic()
{
	// if there's no maps available
	if (m_mapFiles.size() == 0)
	{
		m_state_terminate = true;
		gPacMan.getWindowMgr().pushAnyWindow<MainMenuWindow>();
		gPacMan.getWindowMgr().pushAnyWindow<MessageWindow>(21, 10, 0, 0, L"Error", L"No maps available!");
		return;
	}

	if (gPacMan.isKeyTapped(L'W'))
	{
		--m_menuIndex;
		if (m_menuIndex == m_mapFileNames.size() - 1) // if an underflow occured
			m_firstShownMapIndex = m_mapFileNames.size() - MaxShownMaps;
		else if (m_menuIndex - m_firstShownMapIndex < MaxShownMaps / 2 && m_firstShownMapIndex > 0)
			--m_firstShownMapIndex;
	}
	else if (gPacMan.isKeyTapped(L'S'))
	{
		++m_menuIndex;
		if (m_menuIndex == 0) // if an overflow occured
			m_firstShownMapIndex = 0;
		else if (m_menuIndex - m_firstShownMapIndex > MaxShownMaps / 2 &&
			!((m_mapFileNames.size() - m_menuIndex) < MaxShownMaps / 2))
		{
			++m_firstShownMapIndex;
		}
	}

	if (gPacMan.isKeyTapped(VK_RETURN) && m_mapFiles.size() > 0)
	{
		if (mapHasPlayerSpawn(m_mapFiles[m_menuIndex]))
			gPacMan.getWindowMgr().pushAnyWindow<GameWindow>(m_mapFiles[m_menuIndex]);
		else
			gPacMan.getWindowMgr().pushAnyWindow<MessageWindow>(31, 10, 0, 0, L"Error", L"No player spawn point in map file.");
	}
	else if (gPacMan.isKeyTapped(VK_ESCAPE))
	{
		m_state_terminate = true;
		gPacMan.getWindowMgr().pushAnyWindow<MainMenuWindow>();
	}
}

std::wstring MapSelectorWindow::removeExtension(const std::wstring& path)
{
	return path.substr(0, path.find_last_of(L'.'));
}

void MapSelectorWindow::readMapFiles()
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
	// decrement the upper bound by 1 since the menu index has one more slot
	// than the map list because it begins with 0, whereas the map list vector
	// starts empty. if no map files were inserted by insertIfMapFile, then don't
	// decrement anything.
	if (m_menuIndex.getUpperBound() > 0)
		m_menuIndex.decUpperBound();
}

void MapSelectorWindow::insertIfMapFile(const std::filesystem::path& mapPath)
{
	// if this path doesn't refer to a file, don't do anything
	if (!std::filesystem::is_regular_file(mapPath))
		return;

	MapFile mapFile{ mapPath.c_str() };
	if (!mapFile)
		return;

	m_mapFiles.push_back(mapFile);
	m_mapFileNames.push_back(removeExtension(mapPath.filename().wstring()));
	m_menuIndex.incUpperBound();
}

bool MapSelectorWindow::mapHasPlayerSpawn(const MapFile& map)
{
	for (const std::string& line : map.getData())
		for (char c : line)
			if (c == 'p')
				return true;
	return false;
}

MapSelectorWindow::MapSelectorWindow()
	: Window(WindowType::Other)
{
	readMapFiles();
}