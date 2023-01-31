#pragma once
#include "Window.h"
#include <type_traits>
#include <stack>

using WindowStack_t = std::stack<std::reference_wrapper<Window>>;

class WindowMgr
{
private:
	WindowStack_t m_windowStack{};
};