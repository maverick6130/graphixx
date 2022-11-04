#include <renderer/object.h>

class Sphere : public Object
{
public:
    Sphere(std::shared_ptr<Shader> shader, uint8_t detail_level);
    void SetUpBuffers();
private:
    uint8_t mDetailLevel;
};