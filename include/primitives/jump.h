#include <renderer/object.h>

class Jump : public Object
{
public:
    Jump(std::shared_ptr<Shader> shader, uint8_t detailLevel);
    void SetUpBuffers();
private:
    uint8_t mDetailLevel;

    void AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d);
    void AddTriangle(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c);
};