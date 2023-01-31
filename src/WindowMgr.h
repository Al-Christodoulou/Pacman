#pragma once
#include "IWindow.h"
#include <stack>

using WindowStack_t = std::stack<std::reference_wrapper<IWindow>>;

class WindowMgr
{
private:
	WindowStack_t m_windowStack{};
};