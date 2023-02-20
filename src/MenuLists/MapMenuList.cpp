#include <filesystem>
// these two are needed for wstring => string conversions
#include <locale>
#include <codecvt>
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

std::string MapMenuList::convertToString(const std::wstring& input)
{
	// wstring to string conversion
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter{};
	return converter.to_bytes(input);
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
		m_mapFileNames.push_back(convertToString(mapName));
	}
}