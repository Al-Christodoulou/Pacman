#pragma once
#include <functional>

// a simple menu button, it doesn't need a derived class to function.
// the rendering for it happens on a derived class of either ConstMenuList
// or DynamicMenuList containing menu buttons
class MenuButton
{
private:
	using VoidFunc = std::function<void()>;
	const VoidFunc m_execFunc{ nullptr };

public:
	void onPress() const { m_execFunc(); }

	MenuButton(const VoidFunc& func)
		: m_execFunc{ func }
	{}
};