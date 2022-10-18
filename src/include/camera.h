#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
    virtual glm::mat4 ProjectionMatrix() const;
    virtual void Rotate(float degrees, const glm::vec3& axis);
    virtual void Translate(const glm::vec3& xyz);
};