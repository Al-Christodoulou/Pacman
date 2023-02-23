#include <fstream>
#include <string>
#include "MapFile.h"
#include "Engine/Engine.h"

MapFile::MapFile(const wchar_t* filePath)
{
	m_successful = readFile(filePath);
}

// returns true if the file was successfully read
bool MapFile::readFile(const wchar_t* filePath)
{
	std::ifstream inputFile{ filePath };
	if (!inputFile.good())
		return false;

	std::string buffer{};
	int linesRead{ 0 };
	while (std::getline(inputFile, buffer))
	{
		// if a line doesn't have exactly gScreenWidth length,
		// the file's invalid
		if (buffer.size() != gScreenWidth)
			return false;
		m_lines[linesRead] = buffer;
		++linesRead;
	}

	// if the file doesn't have exactly gScreenHeight lines,
	// it's invalid
	if (linesRead != gScreenHeight)
		return false;
	return true;
}

const MapDataArray& MapFile::getData() { return m_lines; }
MapFile::operator bool() const { return m_successful; }