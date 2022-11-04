#include <heirarchy/pivot_heirarchy.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <queue>
#include <iostream>

#define ROTATION_SPEED 2.0f
#define TRANSLATION_SPEED 2.0f

PivotElement::PivotElement(std::shared_ptr<Object> object, const glm::vec3 &pivot,
                           const glm::vec3 &axis1, const glm::vec3 &axis2, const glm::vec3 &axis3)
    : mObject(object), mPivot(pivot), mRotationAxes({axis1, axis2, axis3})
{
    mPivot = glm::vec3(object->GetModelMatrix() * glm::vec4(mPivot, 1.0f));
    for (auto &axis : mRotationAxes)
    {
        if (glm::l2Norm(axis) != 0.0f)
        {
            glm::vec3 zero = glm::vec3(object->GetModelMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            glm::vec3 axisEndpoint = glm::vec3(object->GetModelMatrix() * glm::vec4(axis, 1.0f));
            axis = glm::normalize(axisEndpoint - zero);
        }
    }
}

glm::mat4 PivotElement::RotatePivotTransform(PivotElement::Axis axis, float angle_in_degrees)
{
    glm::mat4 transform = glm::mat4(1.0f);

    glm::vec3 rotationAxis = mRotationAxes[static_cast<int>(axis)];
    if (glm::l2Norm(rotationAxis) > 0.0f)
    {
        transform = glm::translate(glm::mat4(1.0f), -mPivot) * transform;
        transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle_in_degrees), rotationAxis) * transform;
        transform = glm::translate(glm::mat4(1.0f), mPivot) * transform;
    }

    return transform;
}

glm::mat4 PivotElement::TranslatePivotTransform(PivotElement::Axis axis, float distance)
{
    glm::vec3 rotationAxis = mRotationAxes[static_cast<int>(axis)];
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), rotationAxis * distance);
    return transform;
}

glm::mat4 PivotElement::ScalePivotTransform(PivotElement::Axis axis, float ratio)
{
    glm::vec3 rotationAxis = mRotationAxes[static_cast<int>(axis)];
    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) + rotationAxis * (ratio - 1)); 
    return transform;
}

void PivotElement::ApplyTransform(const glm::mat4 &transform)
{
    mObject->ApplyTransform(transform);
    mPivot = glm::vec3(transform * glm::vec4(mPivot, 1.0f));

    for (auto &axis : mRotationAxes)
    {
        if (glm::l2Norm(axis) != 0.0f)
        {
            glm::vec3 zero = glm::vec3(transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            glm::vec3 axisEndpoint = glm::vec3(transform * glm::vec4(axis, 1.0f));
            axis = glm::normalize(axisEndpoint - zero);
        }
    }
}

void PivotElement::Draw(const Camera &camera)
{
    mObject->Draw(camera);
}

void PivotElement::SetUpBuffers()
{
    mObject->SetUpBuffers();
}

void PivotElement::SetColor(const glm::vec4& color)
{
    mObject->SetColor(color);
}


PivotHeirarchy::PivotHeirarchy(std::shared_ptr<PivotElement> base, glm::vec4 objectColor) : mObjectColor(objectColor)
{
    mObjects.push_back(base);
    mModelTree.push_back({});
    mParentArray.push_back(-1);
}

void PivotHeirarchy::RotatePivot(PivotElement::Axis axis, float angle_in_degrees, uint32_t pivotId)
{
    glm::mat4 transform = mObjects[pivotId]->RotatePivotTransform(axis, angle_in_degrees);
    ApplyTransformRecursive(transform, pivotId);
}

void PivotHeirarchy::TranslatePivot(PivotElement::Axis axis, float distance)
{
    glm::mat4 transform = mObjects[0]->TranslatePivotTransform(axis, distance);
    ApplyTransformRecursive(transform, 0);
}

void PivotHeirarchy::ScalePivot(PivotElement::Axis axis, float ratio)
{
    glm::mat4 transform = mObjects[0]->ScalePivotTransform(axis, ratio);
    ApplyTransformRecursive(transform, 0);
}

uint32_t PivotHeirarchy::AddChild(std::shared_ptr<PivotElement> object, uint32_t parent, glm::vec3 where)
{
    glm::vec3 worldWhere = glm::vec3( mObjects[parent]->mObject->GetModelMatrix() * glm::vec4(where, 1.0f) );
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), worldWhere - object->mPivot);
    
    uint32_t objectId = mObjects.size();
    mObjects.push_back(object);
    mParentArray.push_back(parent);
    mModelTree.push_back({});
    mModelTree[parent].push_back(objectId);
    
    ApplyTransformRecursive(transform, objectId);
    return objectId;
}

void PivotHeirarchy::ApplyTransformRecursive(const glm::mat4& transform, uint32_t base)
{
    std::queue<uint32_t> transformQueue ({base});
    while(!transformQueue.empty())
    {
        uint32_t idx = transformQueue.front();
        transformQueue.pop();
        mObjects[idx]->ApplyTransform(transform);
        for (uint32_t child : mModelTree[idx])
            transformQueue.push(child);
    }
}

void PivotHeirarchy::HandleInput(int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;

    if (!mIsActiveObject)
        return;

    switch (key)
    {
    case GLFW_KEY_O:
        RotatePivot(PivotElement::Axis::ONE, ROTATION_SPEED, mActive);
        break;
    case GLFW_KEY_P:
        RotatePivot(PivotElement::Axis::ONE, -ROTATION_SPEED, mActive);
        break;
    case GLFW_KEY_K:
        RotatePivot(PivotElement::Axis::TWO, ROTATION_SPEED, mActive);
        break;
    case GLFW_KEY_L:
        RotatePivot(PivotElement::Axis::TWO, -ROTATION_SPEED, mActive);
        break;
    case GLFW_KEY_N:
        RotatePivot(PivotElement::Axis::THREE, ROTATION_SPEED, mActive);
        break;
    case GLFW_KEY_M:
        RotatePivot(PivotElement::Axis::THREE, -ROTATION_SPEED, mActive);
        break;

    case GLFW_KEY_Q:
        TranslatePivot(PivotElement::Axis::ONE, -TRANSLATION_SPEED);
        break;
    case GLFW_KEY_W:
        TranslatePivot(PivotElement::Axis::ONE, TRANSLATION_SPEED);
        break;
    case GLFW_KEY_A:
        TranslatePivot(PivotElement::Axis::TWO, -TRANSLATION_SPEED);
        break;
    case GLFW_KEY_S:
        TranslatePivot(PivotElement::Axis::TWO, TRANSLATION_SPEED);
        break;
    case GLFW_KEY_Z:
        TranslatePivot(PivotElement::Axis::THREE, -TRANSLATION_SPEED);
        break;
    case GLFW_KEY_X:
        TranslatePivot(PivotElement::Axis::THREE, TRANSLATION_SPEED);
        break;

    case GLFW_KEY_UP:
        if (mParentArray[mActive] >= 0)
        {
            mActive = mParentArray[mActive];
            mNextToConsider = -1;
        }
        break;
    case GLFW_KEY_DOWN:
        if (mNextToConsider >= 0)
        {
            mActive = mModelTree[mActive][mNextToConsider];
            mNextToConsider = -1;
        }
        break;
    case GLFW_KEY_LEFT:
        if (mNextToConsider >= 0)
        {
            mNextToConsider = (mNextToConsider + 1) % mModelTree[mActive].size();
        }
        break;
    case GLFW_KEY_RIGHT:
        if (mNextToConsider >= 0)
        {
            mNextToConsider = (mNextToConsider + mModelTree[mActive].size() - 1) % mModelTree[mActive].size();
        }
        break;
    default:
        break;
    }
}


void PivotHeirarchy::Draw(const Camera& camera)
{
    if (mNextToConsider < 0 && !mModelTree[mActive].empty())
    {
        mNextToConsider = 0;
    }

    for (int i = 0; i < mObjects.size(); ++i)
    {
        if (i == mActive && mIsActiveObject)
            mObjects[i]->SetColor({1.0f, 0.0f, 0.0f, 1.0f});
        else if (mNextToConsider >= 0 && i == mModelTree[mActive][mNextToConsider] && mIsActiveObject)
            mObjects[i]->SetColor({1.0f, 1.0f, 0.0f, 1.0f});
        else
            mObjects[i]->SetColor(mObjectColor);
        mObjects[i]->Draw(camera);
    }
}

void PivotHeirarchy::SetUpBuffers()
{
    for (auto elem : mObjects)
        elem->SetUpBuffers();
}