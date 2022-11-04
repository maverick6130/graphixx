#include <renderer/object.h>

class Turn : public Object
{
public:
    Turn(std::shared_ptr<Shader> shader, uint8_t detailLevel, float AngleInDegrees, float OuterRadius, float InnerRadius);
    void SetUpBuffers();
private:
    uint8_t mDetailLevel;
    float mAngleInDegrees, mOuterRadius, mInnerRadius;

    void AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d);
    void AddTriangle(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c);
};