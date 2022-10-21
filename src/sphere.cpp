#include <sphere.h>
#include <iostream>

Sphere::Sphere(std::shared_ptr<Shader> shader, uint8_t detail_level)
: Object(GL_TRIANGLES, shader), mDetailLevel(detail_level) {}

void Sphere::SetUpUniforms(const Camera& camera)
{
    mShader->SetUniformMat4("mvp", camera.ProjectionMatrix());
}

void Sphere::SetUpBuffers()
{
    std::vector<glm::vec3> vertices = {
        { 1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0}, { 0.0, 0.0, 1.0},
        {-1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0}, { 0.0, 0.0, 1.0},
        { 1.0, 0.0, 0.0}, { 0.0,-1.0, 0.0}, { 0.0, 0.0, 1.0},
        { 1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0}, { 0.0, 0.0,-1.0},
        {-1.0, 0.0, 0.0}, { 0.0,-1.0, 0.0}, { 0.0, 0.0, 1.0},
        { 1.0, 0.0, 0.0}, { 0.0,-1.0, 0.0}, { 0.0, 0.0,-1.0},
        {-1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0}, { 0.0, 0.0,-1.0},
        {-1.0, 0.0, 0.0}, { 0.0,-1.0, 0.0}, { 0.0, 0.0,-1.0},
    };

    for (uint8_t level = 0; level < mDetailLevel; ++level)
    {
        std::vector<glm::vec3> last_level(vertices);
        vertices.clear();

        for (size_t i = 0; i < last_level.size(); i += 3)
        {
            glm::vec3 mid_01 = (last_level[i] + last_level[i+1])/2.0f;
            glm::vec3 mid_02 = (last_level[i] + last_level[i+2])/2.0f;
            glm::vec3 mid_12 = (last_level[i+1] + last_level[i+2])/2.0f;
            
            vertices.insert(vertices.end(), {
                last_level[i], mid_01, mid_02,
                mid_01, last_level[i+1], mid_12,
                mid_02, mid_01, mid_12,
                mid_02, mid_12, last_level[i+2]
            });
        }
    }

    for (const auto &v : vertices)
        mVertexBuffer.push_back( glm::vec4( glm::normalize(v) , 1.0) );
    
    Object::SetUpBuffers();
}