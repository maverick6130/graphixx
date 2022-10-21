#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <camera.h>
#include <shader.h>

#include <string>
#include <vector>
#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Object
{
public:
    Object(GLuint drawType, std::shared_ptr<Shader> shader);

    void Draw(const Camera& camera);

    virtual void SetUpBuffers();
    virtual void SetUpAttribArray();
    virtual void SetUpUniforms(const Camera& camera);

protected:
    std::vector<glm::vec4> mVertexBuffer;
    size_t mVBOSize = 0;
    std::shared_ptr<Shader> mShader;
    bool mShaderCompile;
    GLuint mDrawType;
    GLuint mVAO = 0, mVBO = 0;
};

class Scene
{
public:
    Scene(std::string_view description);
    size_t AddObject(std::shared_ptr<Object> object);
    void DeleteObject(size_t idx);
    size_t AddCamera(std::shared_ptr<Camera> camera);
    void SetActiveCamera(size_t cameraId);
    void Draw();
private:
    size_t mActiveCamera = 0;
    std::string mDescription;
    std::vector<std::shared_ptr<Object> > mObjects;
    std::vector<std::shared_ptr<Camera> > mCameras;
};