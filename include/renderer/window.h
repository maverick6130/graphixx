#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <renderer/scene.h>

#include <string>
#include <string_view>
#include <utility>

class Window
{
public:
    Window(int width, int height, std::string_view title, std::pair<int,int> openGlVersion, std::shared_ptr<Scene> scene);
    bool IsClosed();
    void RenderForever();
    bool RenderOnce(); // returns true on open windows, false otherwise
    void HandleInput(int key, int scancode, int action, int mods);
    ~Window();

private:
    GLFWwindow* mWindowPtr = NULL;
    std::shared_ptr<Scene> mScene;
    int mWidth = 0, mHeight = 0;
    std::string mTitle;
    std::pair<int,int> mOpenGlVersion;
};