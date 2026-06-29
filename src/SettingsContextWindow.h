#ifndef SETTINGS_CONTEXT_WINDOW_H
#define SETTINGS_CONTEXT_WINDOW_H

#include "ContextWindow.h"
#include <string>
class SettingsContextWindow : public ContextWindow 
{
public:
	SettingsContextWindow(int aAtlasSize, int aPadding);
	void OnImGuiRender() override;

private:
	int mAtlasSize;
	int mAtlasPadding;
};

#endif