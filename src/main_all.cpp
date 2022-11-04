#include <renderer/window.h>
#include <renderer/shader.h>

#include <camera/perspective_camera.h>

#include <heirarchy/pivot_heirarchy.h>
#include <primitives/cylinder.h>
#include <primitives/sphere.h>

#include <utils/utils.h>

extern std::shared_ptr<PivotHeirarchy> CreateRider();
extern std::shared_ptr<PivotHeirarchy> CreateBike();
extern std::shared_ptr<PivotHeirarchy> CreateTrack();

int main(int argc, char* argv[])
{
    std::shared_ptr<Scene> scene = std::make_shared<Scene>("FMX");
    Window w(800, 450, "FMX", {3,3}, scene);
    std::shared_ptr<PivotHeirarchy> rider = CreateRider();
    std::shared_ptr<PivotHeirarchy> bike = CreateBike();
    std::shared_ptr<PivotHeirarchy> track = CreateTrack();

    scene->AddObject(rider);
    scene->AddObject(bike);
    scene->AddObject(track);

    track->TranslatePivot(PivotElement::Axis::ONE, 30.0f);
    track->TranslatePivot(PivotElement::Axis::THREE, -60.0f);

    rider->TranslatePivot(PivotElement::Axis::ONE, 30.0f);
    rider->TranslatePivot(PivotElement::Axis::THREE, -40.0f);

    bike->TranslatePivot(PivotElement::Axis::ONE, 30.0f);
    bike->TranslatePivot(PivotElement::Axis::TWO,  20.0f);
    bike->TranslatePivot(PivotElement::Axis::THREE, -50.0f);

    std::shared_ptr<PerspectiveCamera> camera = std::make_shared<PerspectiveCamera>(
        glm::vec3(-40.0, 0.0, 40.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );
    scene->SetActiveCamera(scene->AddCamera(camera));

    w.RenderForever();
}