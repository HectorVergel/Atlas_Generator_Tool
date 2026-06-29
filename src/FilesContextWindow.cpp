#include "FilesContextWindow.h"
#include "Types.hpp"
#include <GLFW/glfw3.h>
#include <filesystem>

FilesContextWindow::FilesContextWindow(GLFWwindow* aWindow, const ImVec2& windowSize, const ImVec2& windowPosition) :
    mWindowSize(windowSize),
    mWindowPosition(windowPosition)
{
    glfwSetWindowUserPointer(aWindow, this);
    glfwSetDropCallback(aWindow, [](GLFWwindow* window, int count, const char** paths)
    {
        FilesContextWindow* FileCtx = static_cast<FilesContextWindow*>(glfwGetWindowUserPointer(window));
        if (FileCtx)
            FileCtx->OnDrop(window, count, paths);
    });
}

void FilesContextWindow::OnImGuiRender()
{
    ImGui::SetNextWindowSize(mWindowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(mWindowPosition, ImGuiCond_Always);

    ImGui::Begin("Dropped Images");

    if (mDroppedItems.empty())
    {
        ImGui::TextDisabled("No files dropped yet...");
    }
    else
    {
        for (const auto& Path : mDroppedItems)
        {
            ImGui::BulletText("%s", Path.string().c_str());
        }
    }

    // Clear files button

    if (ImGui::Button("Clear")) 
    {
        mDroppedItems.clear();
    }

    ImGui::End();
}

void FilesContextWindow::OnDrop(GLFWwindow* window, int aCount, const char** aPaths)
{
    for (int i = 0; i < aCount; ++i)
    {
        std::filesystem::path Path(aPaths[i]);
        const auto Extension = Path.extension().string();
        if (Extension == ".png" || Extension == ".jpg")
        {
            mDroppedItems.emplace_back(aPaths[i]);
        }
        else
        {
            LOG("WARNING: Ignored unsupported file: " + Path.filename().string());
        }
    }
}

const std::vector<std::filesystem::path>& FilesContextWindow::GetDroppedImages() const
{
    return mDroppedItems;
}
