#include <renderer/shader.h>

#include <camera/perspective_camera.h>

#include <heirarchy/pivot_heirarchy.h>
#include <primitives/cylinder.h>
#include <primitives/sphere.h>

#include <utils/utils.h>

std::shared_ptr<PivotHeirarchy> CreateRider()
{
    std::shared_ptr<Sphere> torso2Shape = std::make_shared<Sphere>(GetShader(), 3);
    torso2Shape->Scale(glm::vec3(2.0f));
    std::shared_ptr<PivotElement> torso2 = std::make_shared<PivotElement>(
        torso2Shape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> torso1Shape = std::make_shared<Cylinder>(GetShader(), 3, 1.5f);
    torso1Shape->Scale(glm::vec3(2.0f));
    std::shared_ptr<PivotElement> torso1 = std::make_shared<PivotElement>(
        torso1Shape, 
        glm::vec3(0.0, 0.0,-1.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> torso3Shape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    torso3Shape->Scale(glm::vec3(-2.0f));
    std::shared_ptr<PivotElement> torso3 = std::make_shared<PivotElement>(
        torso3Shape, 
        glm::vec3(0.0, 0.0,-1.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Sphere> neckShape = std::make_shared<Sphere>(GetShader(), 3);
    neckShape->Scale(glm::vec3(1.0f));
    std::shared_ptr<PivotElement> neck = std::make_shared<PivotElement>(
        neckShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> headShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    headShape->Scale(glm::vec3(1.5f, 1.5f, 1.0f));
    std::shared_ptr<PivotElement> head = std::make_shared<PivotElement>(
        headShape, 
        glm::vec3(0.0, 0.0,-1.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Sphere> shoulderLShape = std::make_shared<Sphere>(GetShader(), 3);
    shoulderLShape->Scale(glm::vec3(1.0f));
    shoulderLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -140.0);
    std::shared_ptr<PivotElement> shoulderL = std::make_shared<PivotElement>(
        shoulderLShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> upperHandLShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    upperHandLShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    upperHandLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -140.0);
    std::shared_ptr<PivotElement> upperHandL = std::make_shared<PivotElement>(
        upperHandLShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> elbowLShape = std::make_shared<Sphere>(GetShader(), 3);
    elbowLShape->Scale(glm::vec3(1.0f));
    elbowLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -180.0);
    std::shared_ptr<PivotElement> elbowL = std::make_shared<PivotElement>(
        elbowLShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0)
    );

    std::shared_ptr<Cylinder> lowerHandLShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    lowerHandLShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    lowerHandLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -180.0);
    std::shared_ptr<PivotElement> lowerHandL = std::make_shared<PivotElement>(
        lowerHandLShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> wristLShape = std::make_shared<Sphere>(GetShader(), 3);
    wristLShape->Scale(glm::vec3(0.5f));
    wristLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -200.0);
    std::shared_ptr<PivotElement> wristL = std::make_shared<PivotElement>(
        wristLShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> fistLShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    fistLShape->Scale(glm::vec3(0.5f, 0.5f, 0.5f));
    fistLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -200.0);
    std::shared_ptr<PivotElement> fistL = std::make_shared<PivotElement>(
        fistLShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> shoulderRShape = std::make_shared<Sphere>(GetShader(), 3);
    shoulderRShape->Scale(glm::vec3(1.0f));
    shoulderRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +140.0);
    std::shared_ptr<PivotElement> shoulderR = std::make_shared<PivotElement>(
        shoulderRShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> upperHandRShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    upperHandRShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    upperHandRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +140.0);
    std::shared_ptr<PivotElement> upperHandR = std::make_shared<PivotElement>(
        upperHandRShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> elbowRShape = std::make_shared<Sphere>(GetShader(), 3);
    elbowRShape->Scale(glm::vec3(1.0f));
    elbowRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +180.0);
    std::shared_ptr<PivotElement> elbowR = std::make_shared<PivotElement>(
        elbowRShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0)
    );

    std::shared_ptr<Cylinder> lowerHandRShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    lowerHandRShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    lowerHandRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +180.0);
    std::shared_ptr<PivotElement> lowerHandR = std::make_shared<PivotElement>(
        lowerHandRShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> wristRShape = std::make_shared<Sphere>(GetShader(), 3);
    wristRShape->Scale(glm::vec3(0.5f));
    wristRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +200.0);
    std::shared_ptr<PivotElement> wristR = std::make_shared<PivotElement>(
        wristRShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> fistRShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    fistRShape->Scale(glm::vec3(0.5f, 0.5f, 0.5f));
    fistRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +200.0);
    std::shared_ptr<PivotElement> fistR = std::make_shared<PivotElement>(
        fistRShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );


    std::shared_ptr<Sphere> hipLShape = std::make_shared<Sphere>(GetShader(), 3);
    hipLShape->Scale(glm::vec3(1.0f));
    hipLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -160.0);
    std::shared_ptr<PivotElement> hipL = std::make_shared<PivotElement>(
        hipLShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> upperLegLShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    upperLegLShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    upperLegLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -160.0);
    std::shared_ptr<PivotElement> upperLegL = std::make_shared<PivotElement>(
        upperLegLShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> kneeLShape = std::make_shared<Sphere>(GetShader(), 3);
    kneeLShape->Scale(glm::vec3(1.0f));
    kneeLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -180.0);
    std::shared_ptr<PivotElement> kneeL = std::make_shared<PivotElement>(
        kneeLShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0)
    );

    std::shared_ptr<Cylinder> lowerLegLShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    lowerLegLShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    lowerLegLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -180.0);
    std::shared_ptr<PivotElement> lowerLegL = std::make_shared<PivotElement>(
        lowerLegLShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> ankleLShape = std::make_shared<Sphere>(GetShader(), 3);
    ankleLShape->Scale(glm::vec3(0.5f));
    ankleLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -180.0);
    std::shared_ptr<PivotElement> ankleL = std::make_shared<PivotElement>(
        ankleLShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> legLShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    legLShape->Scale(glm::vec3(0.5f, 0.5f, 1.25f));
    legLShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, -180.0);
    legLShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, +90.0);
    std::shared_ptr<PivotElement> legL = std::make_shared<PivotElement>(
        legLShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> hipRShape = std::make_shared<Sphere>(GetShader(), 3);
    hipRShape->Scale(glm::vec3(1.0f));
    hipRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +160.0);
    std::shared_ptr<PivotElement> hipR = std::make_shared<PivotElement>(
        hipRShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> upperLegRShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    upperLegRShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    upperLegRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +160.0);
    std::shared_ptr<PivotElement> upperLegR = std::make_shared<PivotElement>(
        upperLegRShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> kneeRShape = std::make_shared<Sphere>(GetShader(), 3);
    kneeRShape->Scale(glm::vec3(1.0f));
    kneeRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +180.0);
    std::shared_ptr<PivotElement> kneeR = std::make_shared<PivotElement>(
        kneeRShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0)
    );

    std::shared_ptr<Cylinder> lowerLegRShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    lowerLegRShape->Scale(glm::vec3(1.0f, 1.0f, 1.5f));
    lowerLegRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +180.0);
    std::shared_ptr<PivotElement> lowerLegR = std::make_shared<PivotElement>(
        lowerLegRShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<Sphere> ankleRShape = std::make_shared<Sphere>(GetShader(), 3);
    ankleRShape->Scale(glm::vec3(0.5f));
    ankleRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +180.0);
    std::shared_ptr<PivotElement> ankleR = std::make_shared<PivotElement>(
        ankleRShape, 
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );

    std::shared_ptr<Cylinder> legRShape = std::make_shared<Cylinder>(GetShader(), 3, 1.0f);
    legRShape->Scale(glm::vec3(0.5f, 0.5f, 1.25f));
    legRShape->Rotate(glm::vec3(0.0f), {1.0f, 0.0f, 0.0f}, +180.0);
    legRShape->Rotate(glm::vec3(0.0f), {0.0f, 1.0f, 0.0f}, +90.0);
    std::shared_ptr<PivotElement> legR = std::make_shared<PivotElement>(
        legRShape, 
        glm::vec3(0.0, 0.0,-1.0)
    );

    std::shared_ptr<PivotHeirarchy> rider = std::make_shared<PivotHeirarchy>(torso2, glm::vec4(0.0, 1.0, 0.0, 1.0));
    uint32_t torso2Id = 0;
    uint32_t torso1Id = rider->AddChild(torso1, torso2Id, {0.0f, 0.0f, 1.0f});
    uint32_t torso3Id = rider->AddChild(torso3, torso2Id, {0.0f, 0.0f,-1.0f});

    uint32_t neckId = rider->AddChild(neck, torso1Id, {0.0f, 0.0f, 1.0f});
    uint32_t headId = rider->AddChild(head, neckId, {0.0f, 0.0f, 1.0f});

    uint32_t shoulderLId = rider->AddChild(shoulderL, torso1Id, {0.0f, 1.5f, 1.0f});
    uint32_t upperHandLId = rider->AddChild(upperHandL, shoulderLId, {0.0f, 0.0f, 1.0f});
    uint32_t elbowLId = rider->AddChild(elbowL, upperHandLId, {0.0f, 0.0f, 1.5f});
    uint32_t lowerHandLId = rider->AddChild(lowerHandL, elbowLId, {0.0f, 0.0f, 1.0f});
    uint32_t wristLId = rider->AddChild(wristL, lowerHandLId, {0.0f, 0.0f, 1.5f});
    uint32_t fistLId = rider->AddChild(fistL, wristLId, {0.0f, 0.0f, 1.0f});

    uint32_t shoulderRId = rider->AddChild(shoulderR, torso1Id, {0.0f, -1.5f, 1.0f});
    uint32_t upperHandRId = rider->AddChild(upperHandR, shoulderRId, {0.0f, 0.0f, 1.0f});
    uint32_t elbowRId = rider->AddChild(elbowR, upperHandRId, {0.0f, 0.0f, 1.5f});
    uint32_t lowerHandRId = rider->AddChild(lowerHandR, elbowRId, {0.0f, 0.0f, 1.0f});
    uint32_t wristRId = rider->AddChild(wristR, lowerHandRId, {0.0f, 0.0f, 1.5f});
    uint32_t fistRId = rider->AddChild(fistR, wristRId, {0.0f, 0.0f, 1.0f});

    uint32_t hipLId = rider->AddChild(hipL, torso3Id, {0.0f, -0.5f, 1.0f});
    uint32_t upperLegLId = rider->AddChild(upperLegL, hipLId, {0.0f, 0.0f, 1.0f});
    uint32_t kneeLId = rider->AddChild(kneeL, upperLegLId, {0.0f, 0.0f, 1.5f});
    uint32_t lowerLegLId = rider->AddChild(lowerLegL, kneeLId, {0.0f, 0.0f, 1.0f});
    uint32_t ankleLId = rider->AddChild(ankleL, lowerLegLId, {0.0f, 0.0f, 1.5f});
    uint32_t legLId = rider->AddChild(legL, ankleLId, {0.0f, 0.0f, 1.0f});

    uint32_t hipRId = rider->AddChild(hipR, torso3Id, {0.0f, 0.5f, 1.0f});
    uint32_t upperLegRId = rider->AddChild(upperLegR, hipRId, {0.0f, 0.0f, 1.0f});
    uint32_t kneeRId = rider->AddChild(kneeR, upperLegRId, {0.0f, 0.0f, 1.5f});
    uint32_t lowerLegRId = rider->AddChild(lowerLegR, kneeRId, {0.0f, 0.0f, 1.0f});
    uint32_t ankleRId = rider->AddChild(ankleR, lowerLegRId, {0.0f, 0.0f, 1.5f});
    uint32_t legRId = rider->AddChild(legR, ankleRId, {0.0f, 0.0f, 1.0f});

    return rider;
}