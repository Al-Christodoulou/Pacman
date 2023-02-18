#pragma once
#include <vector>
#include <initializer_list>
#include "MenuButton.h"

// an abstract class that holds menu buttons, with a selected index
// that increases/decreases based on keyboard input. two derived
// classes exist: ConstMenuList for menu lists that don't change, and
// DynamicMenuList for the opposite
class BaseMenuList
{
private:
	unsigned int m_selectedIndex{ 0 };

public:
	BaseMenuList() = default;
	virtual ~BaseMenuList() = default;

	unsigned int getIndex() { return m_selectedIndex; }

	virtual void handleInput() = 0;

protected:
	// BaseMenuList isn't aware of m_maxIndex because:
	// ConstMenuList's m_maxIndex => const
	// DynamicMenuList's m_maxIndex => non-const,
	// so it has to be passed as a parameter here
	void goUp(unsigned int maxIndex)
	{
		if (m_selectedIndex == 0)
			m_selectedIndex = maxIndex;
		else
			--m_selectedIndex;
	}

	void goDown(unsigned int maxIndex)
	{
		if (m_selectedIndex == maxIndex)
			m_selectedIndex = 0;
		else
			++m_selectedIndex;
	}
};