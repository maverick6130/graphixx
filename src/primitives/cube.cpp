#include <primitives/cube.h>

Cube::Cube(std::shared_ptr<Shader> shader)  
: Object(GL_TRIANGLES, shader) {}

void Cube::SetUpBuffers()
{
    std::vector<glm::vec3> cubeEndpoints = {
        { 1.0,  1.0,  1.0},
        { 1.0, -1.0,  1.0},
        {-1.0, -1.0,  1.0},
        {-1.0,  1.0,  1.0},
        { 1.0,  1.0, -1.0},
        { 1.0, -1.0, -1.0},
        {-1.0, -1.0, -1.0},
        {-1.0,  1.0, -1.0}
    };
    AddQuad(cubeEndpoints[0], cubeEndpoints[1], cubeEndpoints[2], cubeEndpoints[3]);
    AddQuad(cubeEndpoints[0], cubeEndpoints[4], cubeEndpoints[3], cubeEndpoints[7]);
    AddQuad(cubeEndpoints[4], cubeEndpoints[5], cubeEndpoints[6], cubeEndpoints[7]);
    AddQuad(cubeEndpoints[1], cubeEndpoints[5], cubeEndpoints[6], cubeEndpoints[2]);
    AddQuad(cubeEndpoints[0], cubeEndpoints[4], cubeEndpoints[5], cubeEndpoints[1]);
    AddQuad(cubeEndpoints[3], cubeEndpoints[7], cubeEndpoints[6], cubeEndpoints[2]);
    Object::SetUpBuffers();
}

void Cube::AddTriangle(const glm::vec3 &p, const glm::vec3 &q, const glm::vec3&r)
{
    mVertexBuffer.push_back(glm::vec4(p, 1.0));
    mVertexBuffer.push_back(glm::vec4(q, 1.0));
    mVertexBuffer.push_back(glm::vec4(r, 1.0));

}

void Cube::AddQuad(const glm::vec3& a, const::glm::vec3& b, const::glm::vec3& c, const::glm::vec3 &d)
{
    AddTriangle(a, b, c);
    AddTriangle(a, c, d);
}