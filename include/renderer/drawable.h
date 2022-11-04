#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <camera/camera.h>

class Drawable
{
public:
    virtual void Draw(const Camera& camera) = 0;
    virtual void SetUpBuffers() = 0;
    virtual void HandleInput(int key, int scancode, int action, int mods);

    Drawable();

    bool mIsActiveObject;
};