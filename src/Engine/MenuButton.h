#pragma once

typedef void (*VoidFunc)();

// a simple menu button, it doesn't need a derived class to function
class MenuButton
{
private:
	const VoidFunc m_execFunc{ nullptr };

public:
	void onPress() { m_execFunc(); }

	MenuButton(VoidFunc func)
		: m_execFunc{ func }
	{}
};