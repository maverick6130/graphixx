#include <primitives/cylinder.h>

#define _USE_MATH_DEFINES
#include <cmath>

Cylinder::Cylinder(std::shared_ptr<Shader> shader, uint8_t detail_level, float ratio)
: Object(GL_TRIANGLES, shader), mDetailLevel(detail_level), mRatio(ratio) {}

void Cylinder::SetUpBuffers()
{
    size_t N = 1<<(mDetailLevel+2);
    for (size_t i = 0; i < N; ++i)
    {
        double theta1 = i*M_PI*2/N;
        double theta2 = (i+1)*M_PI*2/N;
        float x1 = cos(theta1), y1 = sin(theta1);
        float x2 = cos(theta2), y2 = sin(theta2);
        mVertexBuffer.insert(mVertexBuffer.end(), {
            {0.0, 0.0, 1.0, 1.0}, {mRatio * x1, mRatio * y1, 1.0, 1.0}, {mRatio * x2, mRatio * y2, 1.0, 1.0},
            {mRatio * x1, mRatio * y1, 1.0, 1.0}, {x1, y1,-1.0, 1.0}, {x2, y2,-1.0, 1.0},
            {x2, y2,-1.0, 1.0}, {mRatio * x2, mRatio * y2, 1.0, 1.0}, {mRatio * x1, mRatio * y1, 1.0, 1.0},
            {0.0, 0.0,-1.0, 1.0}, {x2, y2,-1.0, 1.0}, {x1, y1,-1.0, 1.0}
        });
    }
    Object::SetUpBuffers();
}