#include <cassert>
#include "SaveFile.h"

bool SaveFile::open(SaveFileOpenMode sfom)
{
	sfom == SaveFileOpenMode::Read
		? m_file.open("save.bin", std::ios::in | std::ios::binary)
		: m_file.open("save.bin", std::ios::out | std::ios::binary);
	m_openMode = sfom;
	return m_file.good();
}

bool SaveFile::canRead()
{
	return m_file.is_open() && m_file.good() &&
		!m_file.eof() && m_openMode == SaveFileOpenMode::Read;
}

bool SaveFile::canWrite()
{
	return m_file.is_open() && m_file.good() &&
		!m_file.eof() && m_openMode == SaveFileOpenMode::Write;
}

void SaveFile::close()
{
	m_file.close();
}

FontSize SaveFile::readFontSize()
{
	assert(canRead());
	unsigned int value{};
	m_file.read(reinterpret_cast<char*>(&value), sizeof(value));
	return static_cast<FontSize>(value);
}

void SaveFile::writeFontSize(FontSize fs)
{
	assert(canWrite());
	m_file.write(reinterpret_cast<char*>(&fs), sizeof(FontSize));
}