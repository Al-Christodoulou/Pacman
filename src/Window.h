#pragma once

class Window
{
protected:
	// with m_state_begin, the window can setup everything it needs to
	// or play an animation before running its main routines
	bool m_state_begin{ true };
	
	// when set to true, WindowMgr will immediately pop this window from
	// the stack in its next loop
	bool m_state_terminate{ false };

public:
	//virtual void onBegin() = 0;
	virtual void render() = 0;
	virtual void runLogic() = 0;
	//virtual void onEnd() = 0;

	bool doTerminate() const { return m_state_terminate; }
};