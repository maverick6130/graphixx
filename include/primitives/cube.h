#include <renderer/object.h>

class Cube : public Object
{
public:
    Cube(std::shared_ptr<Shader> shader);
    void SetUpBuffers();
private:
    void AddTriangle(const glm::vec3 &p, const glm::vec3 &q, const glm::vec3&r);
    void AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d);
};