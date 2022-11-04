#include <primitives/spool.h>
#include <glm/gtc/matrix_transform.hpp>

Spool::Spool(std::shared_ptr<Shader> shader, uint8_t detail_level_inner, uint8_t detail_level_outer)
 : Object(GL_TRIANGLES, shader), mDetailLevelInner(detail_level_inner), mDetailLevelOuter(detail_level_outer) 
{}

void Spool::SetUpBuffers()
{
    int N = 1<<(mDetailLevelOuter+2);
    int M = 1<<(mDetailLevelInner+2);
    for (int i = 0; i < N; ++i)
    {
        float theta1 = i*360.0/N;
        float theta2 = (i+1)*360.0/N;
        for (int j = 0; j < M; ++j)
        {
            float phi1 = j*360.0/M;
            float phi2 = (j+1)*360.0/M;
            AddQuad(theta1, theta2, phi1, phi2);
        }
    }

    Object::SetUpBuffers();
}

glm::vec4 GetPointOnSpool(float theta, float phi)
{
    glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(theta), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::vec3 axis = glm::vec3(transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    glm::vec3 pivot = glm::vec3(transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    transform = glm::translate(glm::mat4(1.0f), -pivot) * transform;
    transform = glm::rotate(glm::mat4(1.0f), glm::radians(phi), axis) * transform;
    transform = glm::translate(glm::mat4(1.0f),  pivot) * transform;

    return transform * glm::vec4(1.2f, 0.0f, 0.0f, 1.0f);
}

void Spool::AddQuad(float t1, float t2, float f1, float f2)
{
    mVertexBuffer.insert(mVertexBuffer.end(), {
        GetPointOnSpool(t1, f1), GetPointOnSpool(t1, f2), GetPointOnSpool(t2, f1),
        GetPointOnSpool(t1, f2), GetPointOnSpool(t2, f2), GetPointOnSpool(t2, f1)
    });
}