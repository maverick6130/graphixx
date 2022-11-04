#include <renderer/window.h>

#include <heirarchy/pivot_heirarchy.h>

#include <primitives/spool.h>
#include <primitives/cylinder.h>
#include <primitives/sphere.h>

#include <camera/perspective_camera.h>

#include <utils/utils.h>

#define SPOKE_COUNT 16

std::shared_ptr<PivotHeirarchy> CreateBike()
{
    std::shared_ptr<Sphere> engineShape = std::make_shared<Sphere>(GetShader(), 3);
    engineShape->Scale(glm::vec3(3.0f, 6.0f, 1.6f));
    engineShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, -90.0f);
    std::shared_ptr<PivotElement> engine = std::make_shared<PivotElement>(
        engineShape,
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );
    std::shared_ptr<PivotHeirarchy> bike = std::make_shared<PivotHeirarchy>(engine, glm::vec4(0.0, 0.0, 1.0, 0.0));
    uint32_t engineId = 0;

    std::shared_ptr<Cylinder> centerBShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    centerBShape->Scale(glm::vec3(0.5f, 0.5f, 0.8f));
    centerBShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, -90.0f);
    std::shared_ptr<PivotElement> centerB = std::make_shared<PivotElement>(
        centerBShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );
    uint32_t centerBId = bike->AddChild(centerB, engineId, {-1.5f, 1.3f, 0.0f});

    std::shared_ptr<Cylinder> attachment1BShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    attachment1BShape->Scale(glm::vec3(1.0f, 5.0f, 0.1f));
    attachment1BShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, -90.0f);
    attachment1BShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -30.0f);
    std::shared_ptr<PivotElement> attachment1B = std::make_shared<PivotElement>(
        attachment1BShape, glm::vec3(0.0f, -1.0f, 8.0f)
    );
    bike->AddChild(attachment1B, engineId, glm::vec3(0.0f));

    std::shared_ptr<Cylinder> attachment2BShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    attachment2BShape->Scale(glm::vec3(1.0f, 5.0f, 0.1f));
    attachment2BShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, -90.0f);
    attachment2BShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -30.0f);
    std::shared_ptr<PivotElement> attachment2B = std::make_shared<PivotElement>(
        attachment2BShape, glm::vec3(0.0f, -1.0f, -8.0f)
    );
    bike->AddChild(attachment2B, engineId, glm::vec3(0.0f));

    for (int i =0; i < SPOKE_COUNT; ++i)
    {
        std::shared_ptr<Cylinder> spokeShape = std::make_shared<Cylinder>(GetShader(), 0, 1.0f);
        spokeShape->Scale({0.02f, 0.02f, 2.4f});
        spokeShape->Rotate(glm::vec3(0.0f), {-1.0f, 0.0f, 0.0f}, i*180.0/SPOKE_COUNT);
        std::shared_ptr<PivotElement> spoke = std::make_shared<PivotElement>(spokeShape);
        bike->AddChild(spoke, centerBId, {0.0f, 0.0f, 0.0f});
    }

    std::shared_ptr<Spool> wheelBShape = std::make_shared<Spool>(GetShader(), 3, 3);
    wheelBShape->Scale(glm::vec3(3.0f));
    wheelBShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, -90.0f);
    std::shared_ptr<PivotElement> wheelB = std::make_shared<PivotElement>(wheelBShape);
    bike->AddChild(wheelB, centerBId, {0.0f, 0.0f, 0.0f});

    std::shared_ptr<Sphere> frontShape = std::make_shared<Sphere>(GetShader(), 3);
    frontShape->Scale(glm::vec3(2.0f));
    frontShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -30.0f);
    std::shared_ptr<PivotElement> front = std::make_shared<PivotElement>(
        frontShape, 
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    uint32_t frontId = bike->AddChild(front, engineId, {1.0f, -1.0f, 0.0f});

    std::shared_ptr<Cylinder> centerFShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    centerFShape->Scale(glm::vec3(0.5f, 0.5f, 0.8f));
    centerFShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, -90.0f);
    std::shared_ptr<PivotElement> centerF = std::make_shared<PivotElement>(
        centerFShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );
    uint32_t centerFId = bike->AddChild(centerF, frontId, {0.0f, 0.0f, -4.3f});

    for (int i =0; i < SPOKE_COUNT; ++i)
    {
        std::shared_ptr<Cylinder> spokeShape = std::make_shared<Cylinder>(GetShader(), 0, 1.0f);
        spokeShape->Scale({0.02f, 0.02f, 2.4f});
        spokeShape->Rotate(glm::vec3(0.0f), {-1.0f, 0.0f, 0.0f}, i*180.0/SPOKE_COUNT);
        std::shared_ptr<PivotElement> spoke = std::make_shared<PivotElement>(spokeShape);
        bike->AddChild(spoke, centerFId, {0.0f, 0.0f, 0.0f});
    }

    std::shared_ptr<Spool> wheelFShape = std::make_shared<Spool>(GetShader(), 3, 3);
    wheelFShape->Scale(glm::vec3(3.0f));
    wheelFShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, -90.0f);
    std::shared_ptr<PivotElement> wheelF = std::make_shared<PivotElement>(wheelFShape);
    bike->AddChild(wheelF, centerFId, {0.0f, 0.0f, 0.0f});

    std::shared_ptr<Cylinder> handleBar1Shape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    handleBar1Shape->Scale(glm::vec3(0.1f, 0.1f, 4.5f));
    handleBar1Shape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -30.0f);
    std::shared_ptr<PivotElement> handleBar1 = std::make_shared<PivotElement>(
        handleBar1Shape, glm::vec3(8.0f, 0.0f, 1.0f)
    );
    bike->AddChild(handleBar1, frontId, {0.0f, 0.0f, 0.0f});

    std::shared_ptr<Cylinder> handleBar2Shape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    handleBar2Shape->Scale(glm::vec3(0.1f, 0.1f, 4.5f));
    handleBar2Shape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -30.0f);
    std::shared_ptr<PivotElement> handleBar2 = std::make_shared<PivotElement>(
        handleBar2Shape, glm::vec3(-8.0f, 0.0f, 1.0f)
    );
    bike->AddChild(handleBar2, frontId, {0.0f, 0.0f, 0.0f});

    std::shared_ptr<Cylinder> handleShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    handleShape->Scale({0.3f, 0.3f, 4.0f});
    handleShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, 90.0f);
    std::shared_ptr<PivotElement> handle = std::make_shared<PivotElement>(
        handleShape
    );
    bike->AddChild(handle, frontId, glm::vec3(0.0f));

    return bike;
}