#include <renderer/drawable.h>
#include <memory>
#include <vector>

#include <string>
#include <string_view>

class Scene
{
public:
    Scene(std::string_view description);
    size_t AddObject(std::shared_ptr<Drawable> object);
    void DeleteObject(size_t idx);
    size_t AddCamera(std::shared_ptr<Camera> camera);
    void SetActiveCamera(size_t cameraId);
    void Draw();
    void HandleInput(int key, int scancode, int action, int mods);
private:
    size_t mActiveCamera = 0;
    std::string mDescription;
    std::vector<std::shared_ptr<Drawable> > mObjects;
    std::vector<std::shared_ptr<Camera> > mCameras;

    size_t mActiveObject;
};