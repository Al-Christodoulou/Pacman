#pragma once
#include "PacMan.h"
#include <array>

using MapDataArray = std::array<std::string, gScreenHeight>;

class MapFile
{
private:
	// if the file was successfully read
	bool m_successful{ false };
	MapDataArray m_lines{};

public:
	MapFile(const wchar_t*);
	bool readFile(const wchar_t*);
	const MapDataArray& getData();
	operator bool();
};