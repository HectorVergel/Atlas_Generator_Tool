#include "SettingsContextWindow.h"
#include <imgui.h>

SettingsContextWindow::SettingsContextWindow(int aAtlasSize, int aPadding) :
	mAtlasSize(aAtlasSize), 
	mAtlasPadding(aPadding)
{
}

void SettingsContextWindow::OnImGuiRender()
{
	ImGui::Begin("Atlas settings");

	ImGui::InputInt("Atlas Size", &mAtlasSize);
	ImGui::InputInt("Padding", &mAtlasPadding);

	ImGui::End();
}
