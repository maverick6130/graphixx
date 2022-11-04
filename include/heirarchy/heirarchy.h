#include <renderer/object.h>
#include <vector>

class Heirarchy : public Drawable
{
public:
    Heirarchy(std::shared_ptr<Object> base);
    void Draw(const Camera& camera);
    void SetUpBuffers();
    uint32_t AddChild(std::shared_ptr<Object> object, uint32_t parent = 0);
    
    void Scale(const glm::vec3& abc, uint32_t object);
    void Translate(const glm::vec3 &xyz, uint32_t object);
    void Rotate(const glm::vec3& pivot, const glm::vec3& axis, float angle_in_degrees, uint32_t object);

protected:
    std::vector<std::shared_ptr<Object> > mObjects;
    std::vector<std::vector<uint32_t> > mModelTree;
};