#include <renderer/object.h>

class Cylinder : public Object
{
public:
    Cylinder(std::shared_ptr<Shader> shader, uint8_t detail_level, float ratio);
    void SetUpBuffers();
private:
    uint8_t mDetailLevel;
    float mRatio;
};