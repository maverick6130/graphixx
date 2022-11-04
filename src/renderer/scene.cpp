#include <renderer/scene.h>

Scene::Scene(std::string_view desc) : mDescription(desc), mActiveObject(0)
{
    mCameras.push_back(std::shared_ptr<Camera>(new Camera()));
}

size_t Scene::AddCamera(std::shared_ptr<Camera> camera)
{
    mCameras.push_back(camera);
    return mCameras.size() - 1;
}

size_t Scene::AddObject(std::shared_ptr<Drawable> object)
{
    mObjects.push_back(object);
    object->SetUpBuffers();
    if (mObjects.size() - 1 == mActiveObject)
        object->mIsActiveObject = true;
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

void Scene::HandleInput(int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;

    switch (key)
    {
        case GLFW_KEY_1:
        {
            mObjects[mActiveObject]->mIsActiveObject = false;
            mActiveObject = (mActiveObject - 1 + mObjects.size()) % mObjects.size();
            mObjects[mActiveObject]->mIsActiveObject = true;
            break;
        }
        case GLFW_KEY_2:
        {
            mObjects[mActiveObject]->mIsActiveObject = false;
            mActiveObject = (mActiveObject + 1) % mObjects.size();
            mObjects[mActiveObject]->mIsActiveObject = true;
            break;
        }
    }
    for(auto obj : mObjects)
    {
        obj->HandleInput(key, scancode, action, mods);
    }
}

void Scene::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto obj : mObjects)
        obj->Draw(*mCameras[mActiveCamera]);
}