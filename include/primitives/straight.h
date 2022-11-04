#include <renderer/object.h>

class Straight : public Object
{
public:
    Straight(std::shared_ptr<Shader> shader);
    void SetUpBuffers();
};