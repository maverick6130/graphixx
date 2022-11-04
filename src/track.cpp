#include <renderer/window.h>

#include <heirarchy/pivot_heirarchy.h>

#include <primitives/bumps.h>
#include <primitives/straight.h>
#include <primitives/turn.h>
#include <primitives/jump.h>

#include <camera/perspective_camera.h>

#include <utils/utils.h>

#include <iostream>

std::shared_ptr<PivotHeirarchy> CreateTrack()
{
    std::shared_ptr<Bumps> bumps1Shape = std::make_shared<Bumps>(GetShader(), 4, 5, 0.5f, 1.0f);
    bumps1Shape->Scale(glm::vec3(2.0f));
    // bumps1Shape->Translate(glm::vec3(0.0f, -1.0f, 0.0f));
    std::shared_ptr<PivotElement> bumps1 = std::make_shared<PivotElement>(
        bumps1Shape,
        glm::vec3(4.0f, 6.75f, 0.0f), 
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    std::shared_ptr<Straight> straight1Shape = std::make_shared<Straight>(GetShader());
    straight1Shape->Scale(glm::vec3(2.0f, 8.5f, 1.0f));
    // straight1Shape->Translate(glm::vec3(0.0f, 17.5f, 0.0f));
    std::shared_ptr<PivotElement> straight1 = std::make_shared<PivotElement>(straight1Shape);

    std::shared_ptr<Turn> turn1Shape = std::make_shared<Turn>(GetShader(), 3, 180, 5, 3);
    turn1Shape->Scale(glm::vec3(2.0f));
    // turn1Shape->Translate(glm::vec3(8.0f, 26.0f, 0.0f));
    std::shared_ptr<PivotElement> turn1 = std::make_shared<PivotElement>(turn1Shape);

    std::shared_ptr<Jump> jump1Shape = std::make_shared<Jump>(GetShader(), 4);
    jump1Shape->Scale(glm::vec3(2.0f, 3.0f, 3.0f));
    // jump1Shape->Translate(glm::vec3(16.0, 18.5f, 0.0f));
    std::shared_ptr<PivotElement> jump1 = std::make_shared<PivotElement>(jump1Shape);

    std::shared_ptr<Bumps> bumps2Shape = std::make_shared<Bumps>(GetShader(), 4, 3, 1.0f, 0.5f);
    bumps2Shape->Scale(glm::vec3(2.0f));
    bumps2Shape->Rotate(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 180);
    // bumps2Shape->Translate(glm::vec3(16.0, 11.0f, 0.0f));
    std::shared_ptr<PivotElement> bumps2 = std::make_shared<PivotElement>(bumps2Shape);

    std::shared_ptr<Turn> turn2Shape = std::make_shared<Turn>(GetShader(), 3, 180, 5, 3);
    turn2Shape->Scale(glm::vec3(2.0f));
    turn2Shape->Rotate(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 180);
    // turn2Shape->Translate(glm::vec3(8.0, -1.0f, 0.0f));
    std::shared_ptr<PivotElement> turn2 = std::make_shared<PivotElement>(turn2Shape);

    std::shared_ptr<PivotHeirarchy> track = std::make_shared<PivotHeirarchy>(bumps1, glm::vec4(1.0, 0.7, 0.5, 1.0));
    uint8_t bumpsIdx = 0;
    uint8_t straightIdx = track->AddChild(straight1, bumpsIdx, {0.0f, 9.25f, 0.0f});
    uint8_t turnIdx = track->AddChild(turn1, straightIdx, {4.0f, 1.0f, 0.0f});
    uint8_t jumpIdx = track->AddChild(jump1, turnIdx, {4.0f, -3.75f, 0.0f});
    uint8_t bumps2Idx = track->AddChild(bumps2, jumpIdx, {0.0f, -2.5f, 0.0f});
    uint8_t turn2Idx = track->AddChild(turn2, bumps2Idx, {4.0f, 6.0f, 0.0f});

    track->ScalePivot(PivotElement::Axis::ONE, 5.0f);
    track->ScalePivot(PivotElement::Axis::TWO, 7.5f);
    track->ScalePivot(PivotElement::Axis::THREE, 7.5f);
    track->TranslatePivot(PivotElement::Axis::TWO, -101.25f);

    return track;
    
}