#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <renderer/shader.h>
#include <stdexcept>

#define THROW_IF(cond, err) if (cond) throw std::runtime_error(err);

void EnableWireFrameRendering();
void DisableWireFrameRendering();
std::shared_ptr<Shader> GetShader();

namespace Callback
{
    void resize(GLFWwindow *window, int width, int height);
    void error(int error, const char *description);
    void input(GLFWwindow* w, int key, int scancode, int action, int mods);
}