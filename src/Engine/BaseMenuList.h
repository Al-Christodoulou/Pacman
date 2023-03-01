#pragma once
#include <vector>

// an abstract menu list class, with a selected index integer
// that increases/decreases based on keyboard input (inside
// the overwritten handleInput() method
class BaseMenuList
{
private:
	unsigned int m_selectedIndex{ 0 };

public:
	BaseMenuList() = default;
	virtual ~BaseMenuList() = default;

	unsigned int getIndex() { return m_selectedIndex; }
	virtual unsigned int getMaxIndex() = 0;
	virtual void handleInput() = 0;

protected:
	void goUp()
	{
		if (m_selectedIndex == 0)
			m_selectedIndex = getMaxIndex();
		else
			--m_selectedIndex;
	}

	void goDown()
	{
		if (m_selectedIndex == getMaxIndex())
			m_selectedIndex = 0;
		else
			++m_selectedIndex;
	}
};
