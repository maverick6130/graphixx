#include <primitives/turn.h>

#define _USE_MATH_DEFINES
#include <cmath>

Turn::Turn(std::shared_ptr<Shader> shader, uint8_t detailLevel, float angleInDegrees, float OuterRadius, float InnerRadius)
: Object(GL_TRIANGLES, shader), mDetailLevel(detailLevel), mAngleInDegrees(angleInDegrees), mOuterRadius(OuterRadius), mInnerRadius(InnerRadius) {}

void Turn::SetUpBuffers()
{
    size_t N = (1<<(mDetailLevel+2)) * mAngleInDegrees / 30;
    for (size_t i = 0; i < N; ++i)
    {
        float theta1 = i * (mAngleInDegrees * M_PI / 180.0f) / N;
        float theta2 = (i + 1) * (mAngleInDegrees * M_PI / 180.0f) / N;

        float x1 = mInnerRadius * cos(theta1);
        float y1 = mInnerRadius * sin(theta1);
        float x = mOuterRadius * cos(theta2);
        float y2 = mOuterRadius * sin(theta2);

        AddQuad(glm::vec3(mInnerRadius * cos(theta1),  mInnerRadius * sin(theta1), 0.0f), 
                glm::vec3(mInnerRadius * cos(theta2),  mInnerRadius * sin(theta2), 0.0f), 
                glm::vec3(mOuterRadius * cos(theta2),  mOuterRadius * sin(theta2), 0.0f), 
                glm::vec3(mOuterRadius * cos(theta1),  mOuterRadius * sin(theta1), 0.0f));
    }

    Object::SetUpBuffers();
}

void Turn::AddTriangle(const glm::vec3 &p, const glm::vec3 &q, const glm::vec3&r)
{
    mVertexBuffer.push_back(glm::vec4(p, 1.0));
    mVertexBuffer.push_back(glm::vec4(q, 1.0));
    mVertexBuffer.push_back(glm::vec4(r, 1.0));

}

void Turn::AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d)
{
    AddTriangle(a, b, c);
    AddTriangle(a, c, d);
}