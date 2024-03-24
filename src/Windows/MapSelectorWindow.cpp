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
	renderMapList();

	if (m_mapFileNames.size() > MaxShownMaps)
		renderScrollBar();
}

void MapSelectorWindow::renderMapList() const
{
	const size_t maxShownMaps{ std::min(m_mapFileNames.size(), MaxShownMaps) };
	const size_t iGuard{ std::min(m_mapFileNames.size(), m_firstShownMapIndex + maxShownMaps) };
	static constexpr unsigned int cursorToTextDist{ 3 };

	for (size_t i = m_firstShownMapIndex; i < iGuard; i++)
	{
		const std::wstring& mapName{ m_mapFileNames[i] };
		const unsigned int row{ BaseLine + (i - m_firstShownMapIndex) * 2 };
		const unsigned int column{ gScreenWidth / 2 - mapName.size() / 2 };
		gPacMan.sendDataf(mapName.c_str(), mapName.size(), row, column);

		// render the cursor
		if (static_cast<unsigned int>(m_menuIndex) == i)
		{
			const unsigned int textSize{ 1 };
			gPacMan.sendDataf(L"\u25BA", textSize, row, column - cursorToTextDist - textSize);
			gPacMan.sendDataf(L"\u25C4", textSize, row, column + mapName.size() + cursorToTextDist);
		}
	}
}

void MapSelectorWindow::renderScrollBar() const
{
	// the column offset of the scroll bar
	static constexpr unsigned int ColumnOffset{ static_cast<unsigned int>(gScreenWidth * 0.7f) };
	// this divisor is used so the scroll bar is "compressed" so as not to go out of bounds
	// (since its size depends on the amount of maps available)
	static const unsigned int ScrollbarDivisor{ m_mapFileNames.size() / MaxShownMaps };
	static const unsigned int ScrollBarSize{ m_mapFileNames.size() / ScrollbarDivisor };

	// maybe unnecessary sanity check, ColumnOffset would go out of bounds if the width
	// is for some reason less than 7 blocks
	if constexpr (gScreenWidth < 7)
		return;

	// render the horizontal walls of the scroll bar
	gPacMan.sendDataf(L'\u2554', BaseLine, ColumnOffset);
	gPacMan.sendDataf(L'\u2550', BaseLine, ColumnOffset + 1);
	gPacMan.sendDataf(L'\u2557', BaseLine, ColumnOffset + 2);
	gPacMan.sendDataf(L'\u255A', BaseLine + ScrollBarSize, ColumnOffset);
	gPacMan.sendDataf(L'\u2550', BaseLine + ScrollBarSize, ColumnOffset + 1);
	gPacMan.sendDataf(L'\u255D', BaseLine + ScrollBarSize, ColumnOffset + 2);
	// the vertical walls
	for (unsigned int i{ 1 }; i < ScrollBarSize; i++)
	{
		gPacMan.sendDataf(L'\u2551', BaseLine + i, ColumnOffset);
		gPacMan.sendDataf(L'\u2551', BaseLine + i, ColumnOffset + 2);
	}

	// this calculates the size of the inside bar that moves
	const float shownMapsToTotalMapsRatio{ static_cast<float>(MaxShownMaps) / m_mapFileNames.size() };
	const unsigned int innerBarSize{
		std::max(1U, static_cast<unsigned int>((ScrollBarSize - 1) * shownMapsToTotalMapsRatio))
	};

	// render the inner bar
	for (unsigned int i{ 0 }; i < innerBarSize; i++)
	{
		gPacMan.sendDataf(
			L'\u2588',
			BaseLine + 1 + i + m_firstShownMapIndex / ScrollbarDivisor,
			ColumnOffset + 1
		);
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
		// if an underflow occured, m_firstShownMapIndex needs to be updated (unless the total maps
		// is less than MaxShownMaps)
		if (static_cast<size_t>(m_menuIndex) == m_mapFileNames.size() - 1 &&
			m_mapFileNames.size() > MaxShownMaps)
		{
			m_firstShownMapIndex = m_mapFileNames.size() - MaxShownMaps;
		}
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
	static constexpr wchar_t MapFolderName[]{ L"/maps" };
	std::wstring mapFolder{ std::filesystem::current_path().c_str() };
	mapFolder.append(MapFolderName);

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