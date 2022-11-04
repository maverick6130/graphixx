#include <renderer/window.h>
#include <renderer/shader.h>

#include <camera/perspective_camera.h>

#include <heirarchy/pivot_heirarchy.h>
#include <primitives/cylinder.h>
#include <primitives/sphere.h>

#include <utils/utils.h>

extern std::shared_ptr<PivotHeirarchy> CreateBike();

int main(int argc, char* argv[])
{
    std::shared_ptr<Scene> scene = std::make_shared<Scene>("Bike");
    Window w(800, 450, "Bike", {3,3}, scene);
    std::shared_ptr<PivotHeirarchy> bike = CreateBike();
    scene->AddObject(bike);

    std::shared_ptr<PerspectiveCamera> camera = std::make_shared<PerspectiveCamera>(
        glm::vec3(-40.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );
    scene->SetActiveCamera(scene->AddCamera(camera));
    
    w.RenderForever();
}