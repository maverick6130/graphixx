#include <renderer/object.h>

class Spool : public Object
{
public:
    Spool(std::shared_ptr<Shader> shader, uint8_t detail_level_inner, uint8_t detail_level_outer);
    void SetUpBuffers();
private:
    void AddQuad(float, float, float, float);
    uint8_t mDetailLevelInner, mDetailLevelOuter;
};