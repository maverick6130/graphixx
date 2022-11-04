#include <primitives/jump.h>

#define _USE_MATH_DEFINES
#include <cmath>

Jump::Jump(std::shared_ptr<Shader> shader, uint8_t detailLevel)
: Object(GL_TRIANGLES, shader), mDetailLevel(detailLevel) {}

void Jump::SetUpBuffers()
{
    AddQuad(glm::vec3(1.0, -2.5, 0.0),
            glm::vec3(1.0, -1.0, 2.0),
            glm::vec3(-1.0, -1.0, 2.0),
            glm::vec3(-1.0, -2.5, 0.0));

    size_t N = (1<<(mDetailLevel+2));
    for (size_t i = 0; i < N; ++i)
    {
        float y1 = i * 2.0f / N - 1;
        float y2 = (i + 1) * 2.0f / N - 1;
        float z1 = 2 * y1 * y1;
        float z2 = 2 * y2 * y2;

        AddQuad(glm::vec3(1.0, y1, z1), glm::vec3(1.0f, y2, z2), glm::vec3(-1.0f, y2, z2), glm::vec3(-1.0f, y1, z1));
    }

    AddQuad(glm::vec3(1.0, 1.0, 2.0),
            glm::vec3(1.0, 2.5, 0.0),
            glm::vec3(-1.0, 2.5, 0.0),
            glm::vec3(-1.0, 1.0, 2.0));

    Object::SetUpBuffers();
}

void Jump::AddTriangle(const glm::vec3 &p, const glm::vec3 &q, const glm::vec3&r)
{
    mVertexBuffer.push_back(glm::vec4(p, 1.0));
    mVertexBuffer.push_back(glm::vec4(q, 1.0));
    mVertexBuffer.push_back(glm::vec4(r, 1.0));

}

void Jump::AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d)
{
    AddTriangle(a, b, c);
    AddTriangle(a, c, d);
}