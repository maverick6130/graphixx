#pragma once

#include <camera.h>

class PerspectiveCamera : public Camera
{
    glm::vec3 mEye, mLookat, mUp;
    float mFov, mAspectRatio, mNear, mFar;
public:
    PerspectiveCamera(const glm::vec3& eye, const glm::vec3& lookat, const glm::vec3& up, float fov = 60.0,
        float aspect_ratio = 4.0/3.0, float near = 0.1, float far = 1000.0);
    glm::mat4 ProjectionMatrix() const;
    void Rotate(float degrees, const glm::vec3& axis);
    void Translate(const glm::vec3& xyz);
};