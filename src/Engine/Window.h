#pragma once

class WindowMgr;

template <typename WindowTypes>
class Window
{
	friend class WindowMgr;

protected:
	// with m_state_begin, the window can setup everything it needs to
	// or play an animation before running its main routines
	bool m_state_begin{ true };
	
	// when set to true, WindowMgr will immediately pop this window from
	// the stack in its next loop
	bool m_state_terminate{ false };

	WindowTypes m_winType{};

public:
	//virtual void onBegin() = 0;
	virtual void render() = 0;
	virtual void runLogic() = 0;
	virtual void postMoveInit() {};
	//virtual void onEnd() = 0;

	Window(WindowTypes winType)
		: m_winType{ winType }
	{}

	virtual ~Window() = default;
	Window(const Window&) = delete;
	Window(Window&&) = delete;

	WindowTypes getWindowType() const { return m_winType; }

	bool doTerminate() const { return m_state_terminate; }
};