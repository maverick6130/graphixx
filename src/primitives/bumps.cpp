#include <primitives/bumps.h>

#define _USE_MATH_DEFINES
#include <cmath>

Bumps::Bumps(std::shared_ptr<Shader> shader, uint8_t detailLevel, uint8_t numberBumps, float amplitude, float frequency)
: Object(GL_TRIANGLES, shader), mDetailLevel(detailLevel), mNumberBumps(numberBumps), mAmplitude(amplitude), mFrequency(frequency) {}

void Bumps::SetUpBuffers()
{
    size_t N = (1<<(mDetailLevel+2)) * mNumberBumps;
    for (size_t i = 0; i < N; ++i)
    {
        float y1 = (i * mNumberBumps / mFrequency) / N;
        float y2 = ((i+1) * mNumberBumps / mFrequency) / N;
        float z1 = mAmplitude * sin(M_PI * mFrequency * y1) * sin(M_PI * mFrequency * y1);
        float z2 = mAmplitude * sin(M_PI * mFrequency * y2) * sin(M_PI * mFrequency * y2);

        AddQuad(glm::vec3(1.0, y1, z1), glm::vec3(1.0f, y2, z2), glm::vec3(-1.0f, y2, z2), glm::vec3(-1.0f, y1, z1));
    }

    Object::SetUpBuffers();
}

void Bumps::AddTriangle(const glm::vec3 &p, const glm::vec3 &q, const glm::vec3&r)
{
    mVertexBuffer.push_back(glm::vec4(p, 1.0));
    mVertexBuffer.push_back(glm::vec4(q, 1.0));
    mVertexBuffer.push_back(glm::vec4(r, 1.0));

}

void Bumps::AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d)
{
    AddTriangle(a, b, c);
    AddTriangle(a, c, d);
}