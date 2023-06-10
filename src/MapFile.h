#pragma once
#include "PacMan.h"
#include <string>
#include <array>

using MapDataArray = std::array<std::string, gPlayableSpaceHeight>;

class MapFile
{
private:
	// if the file was successfully read
	bool m_successful{ false };
	MapDataArray m_lines{};

public:
	MapFile(const wchar_t*);
	bool readFile(const wchar_t*);
	const MapDataArray& getData() const;
	operator bool() const;
};