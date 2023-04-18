#pragma once
#include <cassert>

// an integer that has a custom overflow-underflow limit, very
// useful for menu indices
class CustomInt
{
private:
	int m_lowerBound, m_upperBound, m_index;

public:
	CustomInt(int lowerBound, int upperBound)
		: m_lowerBound{ lowerBound }, m_upperBound{ upperBound }
	{
		assert(lowerBound <= upperBound);
		m_index = m_lowerBound;
	}

	CustomInt(int lowerBound, int upperBound, int startingValue)
		: CustomInt(lowerBound, upperBound)
	{
		m_index = startingValue;
	}

	CustomInt& operator++()
	{
		if (m_index == m_upperBound)
			m_index = m_lowerBound;
		else
			++m_index;
		return *this;
	}

	CustomInt operator++(int)
	{
		CustomInt temp{ *this };
		++(*this);
		return temp;
	}

	CustomInt& operator--()
	{
		if (m_index == m_lowerBound)
			m_index = m_upperBound;
		else
			--m_index;
		return *this;
	}

	CustomInt operator--(int)
	{
		CustomInt temp{ *this };
		--(*this);
		return temp;
	}

	operator int() const
	{
		return m_index;
	}

	void incUpperBound() { ++m_upperBound; }
	void decUpperBound() { --m_upperBound; }
};