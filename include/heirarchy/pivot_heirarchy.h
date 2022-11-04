#include <renderer/object.h>

class PivotElement : public Drawable
{
public:
    PivotElement(std::shared_ptr<Object> object, 
                    const glm::vec3& pivot = glm::vec3(0.0f), 
                    const glm::vec3& axis1 = glm::vec3(0.0f),
                    const glm::vec3& axis2 = glm::vec3(0.0f),
                    const glm::vec3& axis3 = glm::vec3(0.0f)
    );
    enum class Axis 
    {
        ONE, TWO, THREE
    };
    
    void Draw(const Camera& camera);
    void SetUpBuffers();
    void SetColor(const glm::vec4& color);
    glm::mat4 RotatePivotTransform(Axis axis, float angle_in_degrees);
    glm::mat4 TranslatePivotTransform(Axis axis, float distance);
    glm::mat4 ScalePivotTransform(Axis axis, float ratio);

private:
    void ApplyTransform(const glm::mat4& transform);
    
    std::shared_ptr<Object> mObject;
    std::vector<glm::vec3> mRotationAxes;
    glm::vec3 mPivot;

    friend class PivotHeirarchy;
};

class PivotHeirarchy : public Drawable
{
public:
    PivotHeirarchy(std::shared_ptr<PivotElement> base, glm::vec4 objectColor = glm::vec4(1.0f));
    void Draw(const Camera& camera);
    void SetUpBuffers();

    void RotatePivot(PivotElement::Axis axis, float angle_in_degrees, uint32_t pivotId);
    void TranslatePivot(PivotElement::Axis axis, float distance);
    void ScalePivot(PivotElement::Axis axis, float ratio);

    uint32_t AddChild(std::shared_ptr<PivotElement> object, uint32_t parent, glm::vec3 where);

    void HandleInput(int key, int scancode, int action, int mods);

private:
    void ApplyTransformRecursive(const glm::mat4& transform, uint32_t base);
    std::vector<std::shared_ptr<PivotElement> > mObjects;
    std::vector<std::vector<uint32_t> > mModelTree;
    std::vector<int> mParentArray;

    int mActive = 0;
    int mNextToConsider = -1;
    glm::vec4 mObjectColor;
};