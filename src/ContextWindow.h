#ifndef CONTEXT_WINDOW_H
#define CONTEXT_WINDOW_H

#include <imgui.h>

class ContextWindow 
{
public:
	virtual ~ContextWindow() = default;
	virtual void OnImGuiRender() = 0;

protected:
	ImVec2 mWindowSize;
	ImVec2 mWindowPosition;
};

#endif