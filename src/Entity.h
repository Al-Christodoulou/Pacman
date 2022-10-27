#pragma once
#include "Engine.h"

class Entity
{
protected:
	float m_x{ gScreenWidth / 2 }, m_y{ gScreenHeight / 2 };
	wchar_t m_texture{ L'#' };

public:
	static unsigned int interpretXY(float, float);
	unsigned int getPos() const;
	float getVirtualX() const;
	float getVirtualY() const;
	wchar_t getTex() const;

	Entity(int, int, wchar_t);
	Entity(wchar_t);
};