#include <window.h>
#include <sphere.h>
#include <cube.h>
#include <perspective_camera.h>

int main(int argc, char* argv[])
{
    std::shared_ptr<Scene> scene = std::make_shared<Scene>("A simple triangle");
    Window w(1024, 768, "Voxel Modelling", {3,3}, scene);
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("src/shader/vs.glsl", "src/shader/fs.glsl");
    std::shared_ptr<Sphere> shape = std::make_shared<Sphere>(shader, 4);
    std::shared_ptr<PerspectiveCamera> camera = std::make_shared<PerspectiveCamera>(
        glm::vec3(3.0, 3.0, 3.0), 
        glm::vec3(0.0, 0.0, 0.0), 
        glm::vec3(1.0, 0.0, 0.0)
    );
    scene->AddObject(shape);
    scene->SetActiveCamera(scene->AddCamera(camera));
    w.RenderForever();
}