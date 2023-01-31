#pragma once

class IWindow
{
public:
	//virtual void onBegin() = 0;
	virtual void render() = 0;
	virtual void runLogic() = 0;
	//virtual void onEnd() = 0;
};