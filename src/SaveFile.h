#pragma once
#include <fstream>
#include "Engine/EngineStructs.h"

enum class SaveFileOpenMode
{
	Read = 0,
	Write
};

class SaveFile
{
private:
	std::fstream m_file{};
	SaveFileOpenMode m_openMode{};

public:
	bool open(SaveFileOpenMode);
	bool canRead();
	bool canWrite();
	void close();

	FontSize readFontSize();
	void writeFontSize(FontSize);
};