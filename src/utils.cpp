#include <utils.h>
#include <iostream>

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
}