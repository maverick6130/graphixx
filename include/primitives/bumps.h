#include <renderer/object.h>

class Bumps : public Object
{
public:
    Bumps(std::shared_ptr<Shader> shader, uint8_t detailLevel, uint8_t numberBumps, float amplitude, float frequency);
    void SetUpBuffers();
private:
    uint8_t mDetailLevel, mNumberBumps;
    float mAmplitude, mFrequency;

    void AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d);
    void AddTriangle(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c);
};