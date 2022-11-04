#include <renderer/object.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/projection.hpp>

Object::Object(GLuint drawType, std::shared_ptr<Shader> shader)
    : mShader(shader), mDrawType(drawType)
{
    if (mShader)
    {
        mShaderCompile = mShader->Compile();
        if (!mShaderCompile)
            mShader->PrintErrorLog();
    }
}

void Object::Draw(const Camera &camera)
{
    if (mShaderCompile)
    {        
        mShader->Bind();
        SetUpUniforms(camera);
        glBindVertexArray(mVAO);
        glDrawArrays(mDrawType, 0, mVBOSize);
        glBindVertexArray(0);
        mShader->UnBind();
    }
}

// Expected derivation - derive SetupAttribArray() according to shader, set mVertexBuffer and call parent's
void Object::SetUpBuffers()
{
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertexBuffer.size()* sizeof(glm::vec4), mVertexBuffer.data(), GL_STATIC_DRAW);
    
    mVBOSize = mVertexBuffer.size();
    mVertexBuffer.erase(mVertexBuffer.begin(), mVertexBuffer.end());

    SetUpAttribArray();

    glBindVertexArray(0);
}

void Object::SetUpAttribArray()
{
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Object::SetUpUniforms(const Camera& camera)
{
    mShader->SetUniformVec4("color", mColor);
    mShader->SetUniformMat4("model_matrix", mModelMatrix);
    mShader->SetUniformMat4("view_proj_matrix", camera.ProjectionMatrix());
}

void Object::SetColor(const glm::vec4& color)
{
    mColor = color;
}

void Object::Scale(const glm::vec3& abc)
{
    mModelMatrix = glm::scale(glm::mat4(1.0f), abc) * mModelMatrix;
}

void Object::Translate(const glm::vec3 &xyz)
{
    mModelMatrix = glm::translate(glm::mat4(1.0f), xyz) * mModelMatrix;
}

void Object::Rotate(const glm::vec3& pivot, const glm::vec3& axis, float angle_in_degrees)
{
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, pivot);
    transform = glm::rotate(transform, glm::radians(angle_in_degrees), axis);
    transform = glm::translate(transform, -pivot);
    mModelMatrix = transform * mModelMatrix;
}

glm::mat4 Object::GetModelMatrix()
{
    return mModelMatrix;
}

void Object::ApplyTransform(const glm::mat4& transform)
{
    mModelMatrix = transform * mModelMatrix;
}