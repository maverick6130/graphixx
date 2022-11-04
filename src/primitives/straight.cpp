#include <primitives/straight.h>

Straight::Straight(std::shared_ptr<Shader> shader)
: Object(GL_TRIANGLES, shader) {}

void Straight::SetUpBuffers()
{
    mVertexBuffer.push_back(glm::vec4(1.0, 1.0, 0.0, 1.0));
    mVertexBuffer.push_back(glm::vec4(1.0, -1.0, 0.0, 1.0));
    mVertexBuffer.push_back(glm::vec4(-1.0, -1.0, 0.0, 1.0));
    mVertexBuffer.push_back(glm::vec4(1.0, 1.0, 0.0, 1.0));
    mVertexBuffer.push_back(glm::vec4(-1.0, -1.0, 0.0, 1.0));
    mVertexBuffer.push_back(glm::vec4(-1.0, 1.0, 0.0, 1.0));

    Object::SetUpBuffers();
}