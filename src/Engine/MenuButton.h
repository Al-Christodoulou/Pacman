#pragma once

typedef void (*VoidFunc)();

// a simple menu button, it doesn't need a derived class to function.
// the rendering for it happens on a MenuList containing menu buttons
class MenuButton
{
private:
	const VoidFunc m_execFunc{ nullptr };

public:
	void onPress() const { m_execFunc(); }

	MenuButton(VoidFunc func)
		: m_execFunc{ func }
	{}
};