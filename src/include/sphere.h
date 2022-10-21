#include <scene.h>

class Sphere : public Object
{
public:
    Sphere(std::shared_ptr<Shader> shader, uint8_t detail_level);
    void SetUpBuffers();
    void SetUpUniforms(const Camera& camera);
private:
    uint8_t mDetailLevel;
};