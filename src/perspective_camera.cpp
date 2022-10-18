#include <perspective_camera.h>
#include <glm/gtx/transform.hpp>

PerspectiveCamera::PerspectiveCamera(const glm::vec3& eye, const glm::vec3& lookat, const glm::vec3& up,
               float fov, float aspect_ratio, float near, float far)
{
    mEye = eye;
    mLookat = lookat;
    mUp = up;
    mFov = fov;
    mAspectRatio = aspect_ratio;
    mNear = near;
    mFar = far;
}

void PerspectiveCamera::Rotate(float degrees, const glm::vec3& axis)
{
    glm::mat4 rotate = glm::rotate(glm::radians(degrees), axis);
    glm::vec4 rotated_up = rotate * glm::vec4(mUp, 1.0);
    mUp = glm::vec3(rotated_up[0] / rotated_up[3], rotated_up[1] / rotated_up[3], rotated_up[2] / rotated_up[3]);
    glm::vec4 rotated_eye = rotate * glm::vec4(mEye - mLookat, 1.0);
    mEye = glm::vec3(rotated_eye[0] / rotated_eye[3], rotated_eye[1] / rotated_eye[3], rotated_eye[2] / rotated_eye[3]) + mLookat;
}

void PerspectiveCamera::Translate(const glm::vec3& xyz)
{
    mEye += xyz;
    mLookat += xyz;
}

glm::mat4 PerspectiveCamera::ProjectionMatrix() const
{
    glm::mat4 view = glm::lookAt(mEye, mLookat, mUp);
    glm::mat4 proj = glm::perspective(glm::radians(mFov), mAspectRatio, mNear, mFar);
    return proj * view;
}