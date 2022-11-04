#include <heirarchy/heirarchy.h>

Heirarchy::Heirarchy(std::shared_ptr<Object> object)
{
    mObjects.push_back(object);
    mModelTree.push_back({});
}

void Heirarchy::Draw(const Camera& camera)
{
    for (auto obj : mObjects)
        obj->Draw(camera);
}

void Heirarchy::SetUpBuffers()
{
    for (auto obj : mObjects)
        obj->SetUpBuffers();
}

uint32_t Heirarchy::AddChild(std::shared_ptr<Object> object, uint32_t parent)
{
    mObjects.push_back(object);
    mModelTree.push_back({});
    uint32_t id = mObjects.size() - 1;
    mModelTree[parent].push_back(id);
    return id;
}

void Heirarchy::Scale(const glm::vec3& abc, uint32_t object)
{
    mObjects[object]->Scale(abc);
    for (auto child : mModelTree[object])
        Scale(abc, child);
}

void Heirarchy::Translate(const glm::vec3 &xyz, uint32_t object)
{
    mObjects[object]->Translate(xyz);
    for (auto child : mModelTree[object])
        Translate(xyz, child);
}

void Heirarchy::Rotate(const glm::vec3& pivot, const glm::vec3& axis, float angle_in_degrees, uint32_t object)
{
    mObjects[object]->Rotate(pivot, axis, angle_in_degrees);
    for (auto child : mModelTree[object])
        Rotate(pivot, axis, angle_in_degrees, child);
}