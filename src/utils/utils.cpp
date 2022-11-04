#include <utils/utils.h>
#include <renderer/window.h>

#include <iostream>

void EnableWireFrameRendering()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void DisableWireFrameRendering()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

std::shared_ptr<Shader> GetShader()
{
    return std::make_shared<Shader>("shader/vs.glsl", "shader/fs.glsl");
}

namespace Callback
{
    void resize(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void error(int error, const char *description)
    {
        std::cerr << error << " : " << description << std::endl;
    }

    void input(GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        reinterpret_cast<Window*>(glfwGetWindowUserPointer(w))->HandleInput(key, scancode, action, mods);
    }
}