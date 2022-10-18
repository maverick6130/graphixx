#include <window.h>

class Triangle : public Object
{
public:
    Triangle(std::shared_ptr<Shader> shader) : Object(GL_TRIANGLES, shader) {}
    void SetUpUniforms() {}
    void SetUpBuffers() 
    {
        mVertexBuffer.push_back(glm::vec4(0.0, 0.5, 0.0, 1.0));
        mVertexBuffer.push_back(glm::vec4(0.5, -0.5, 0.0, 1.0));
        mVertexBuffer.push_back(glm::vec4(-0.5, -0.5, 0.0, 1.0));
        Object::SetUpBuffers();
    }
};

int main(int argc, char* argv[])
{
    std::shared_ptr<Scene> scene(new Scene("A simple triangle"));
    Window w(1024, 768, "Voxel Modelling", {3,3}, scene);
    std::shared_ptr<Shader> shader(new Shader("src/shader/vs.glsl", "src/shader/fs.glsl"));
    std::shared_ptr<Triangle> triangle(new Triangle(shader));
    scene->AddObject(triangle);
    w.RenderForever();
}