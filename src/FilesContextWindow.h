#ifndef FILES_CONTEXT_WINDOW_H
#define FILES_CONTEXT_WINDOW_H

#include <vector>
#include <imgui.h>
#include <filesystem>
#include "ContextWindow.h"

struct GLFWwindow;

class FilesContextWindow : public ContextWindow
{
public:
	FilesContextWindow(GLFWwindow* aWindow, const ImVec2& windowSize, const ImVec2& windowPosition);
	~FilesContextWindow() = default;
	void OnImGuiRender() override;
	void OnDrop(GLFWwindow* window, int aCount, const char** aPaths);
	const std::vector<std::filesystem::path>& GetDroppedImages() const;

private:

	std::vector<std::filesystem::path> mDroppedItems;
	ImVec2 mWindowSize;
	ImVec2 mWindowPosition;
};

#endif