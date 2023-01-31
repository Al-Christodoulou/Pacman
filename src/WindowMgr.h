#pragma once
#include <stack>

class WindowMgr
{
private:
	std::stack<std::reference_wrapper<IWindow>> m_windowStack{};
};