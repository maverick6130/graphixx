#include <window.h>
#include <iostream>
#include <utils.h>

Window::Window(int width, int height, std::string_view title, std::pair<int,int> openGlVersion, std::shared_ptr<Scene> scene)
 : mWidth(width), mHeight(height), mTitle(title), mOpenGlVersion(openGlVersion), mScene(scene)
{
    THROW_IF(!glfwInit(), "Could not initialize GLFW3");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mOpenGlVersion.first);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mOpenGlVersion.second);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindowPtr = glfwCreateWindow(width, height, mTitle.c_str(), NULL, NULL);
    if (!mWindowPtr)
    {
        glfwTerminate();
        std::cerr << "Could not initialize window" << std::endl;
        throw;
    }

    glfwMakeContextCurrent(mWindowPtr);

    glewExperimental = GL_TRUE;
    GLuint err = glewInit();
    if (err == GLEW_OK)
    {
        std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Supported OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Supported GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    }
    else
    {
        glfwTerminate();
        std::cerr << "Could not initialize GLEW" << std::endl;
        mWindowPtr = NULL;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glfwSetWindowUserPointer(mWindowPtr, reinterpret_cast<void *>(this));
    glfwSetFramebufferSizeCallback(mWindowPtr, Callback::resize);
    glfwSetErrorCallback(Callback::error);
}

bool Window::IsClosed()
{
    THROW_IF(!mWindowPtr, "Uninitialized window");
    if (glfwWindowShouldClose(mWindowPtr))
        return true;
    return false;
}

bool Window::RenderOnce()
{
    if (IsClosed())
        return false;
    glfwPollEvents();
    mScene->Draw();
    glfwSwapBuffers(mWindowPtr);
    return true;
}

void Window::RenderForever()
{
    while(RenderOnce());
}

Window::~Window()
{
    glfwTerminate();
}