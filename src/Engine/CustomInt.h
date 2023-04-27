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
		assert(startingValue >= m_lowerBound && startingValue <= m_upperBound);
		m_index = startingValue;
	}

	CustomInt& operator++()
	{
		if (m_index == m_upperBound)
			m_index = m_lowerBound;
		else
			++m_index;
		assert(m_index >= m_lowerBound && m_index <= m_upperBound);
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
		assert(m_index >= m_lowerBound && m_index <= m_upperBound);
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

	void incUpperBound()
	{
		assert(m_lowerBound <= m_upperBound + 1);
		++m_upperBound;
	}

	void decUpperBound()
	{
		assert(m_lowerBound <= m_upperBound - 1);
		--m_upperBound;
	}

	int getLowerBound() const { return m_lowerBound; }
	int getUpperBound() const { return m_upperBound; }
};