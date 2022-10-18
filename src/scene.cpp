#include <scene.h>

Object::Object(GLuint drawType, std::shared_ptr<Shader> shader)
    : mShader(shader), mDrawType(drawType)
{
    mShaderCompile = mShader->Compile();
    if (!mShaderCompile)
        mShader->PrintErrorLog();
}

void Object::Draw(const Camera &camera)
{
    if (mShaderCompile)
    {        
        mShader->Bind();
        SetUpUniforms();
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

void Object::SetUpUniforms()
{
}

Scene::Scene(std::string_view desc) : mDescription(desc)
{
    mCameras.push_back(std::shared_ptr<Camera>(new Camera()));
}

size_t Scene::AddCamera(std::shared_ptr<Camera> camera)
{
    mCameras.push_back(camera);
    return mCameras.size() - 1;
}

size_t Scene::AddObject(std::shared_ptr<Object> object)
{
    mObjects.push_back(object);
    object->SetUpBuffers();
    return mObjects.size() - 1;
}

void Scene::DeleteObject(size_t idx)
{
    if (idx < mObjects.size())
        mObjects.erase(mObjects.begin() + idx);
}

void Scene::SetActiveCamera(size_t idx)
{
    mActiveCamera = idx;
}

void Scene::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto obj : mObjects)
        obj->Draw(*mCameras[mActiveCamera]);
}