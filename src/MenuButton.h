#pragma once

typedef void (*VoidFunc)();

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