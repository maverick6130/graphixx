#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#define THROW_IF(cond, err) if (cond) throw std::runtime_error(err);

namespace Callback
{
    void resize(GLFWwindow *window, int width, int height);
    void error(int error, const char *description);
}