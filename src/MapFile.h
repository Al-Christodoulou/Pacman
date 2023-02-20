#pragma once
#include <array>

using MapDataArray = std::array<std::string, gScreenHeight>;

class MapFile
{
private:
	// if the file was successfully read
	bool m_successful{ false };
	MapDataArray m_lines{};

public:
	MapFile(const char*);
	bool readFile(const char*);
	const MapDataArray& getData();
	operator bool();
};