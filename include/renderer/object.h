#pragma once

#include <renderer/drawable.h>
#include <renderer/shader.h>

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Object : public Drawable
{
public:
    Object(GLuint drawType, std::shared_ptr<Shader> shader);

    void Translate(const glm::vec3& xyz);
    void Scale(const glm::vec3& abc);
    void Rotate(const glm::vec3& pivot, const glm::vec3& axis, float angle_in_degrees);
    void ApplyTransform(const glm::mat4& transform);
    glm::mat4 GetModelMatrix();
    
    void SetColor(const glm::vec4& color);

    virtual void Draw(const Camera& camera);
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
    glm::mat4 mModelMatrix = glm::mat4(1.0f);
    glm::vec4 mColor = glm::vec4(1.0f);
};