#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string_view>
#include <string>
#include <sstream>

#include <glm/mat4x4.hpp>

/*
    Correct sequence of operations for a draw call in Object -
    1. compile shader and check for error!
    2. bind shader
    3. set uniforms
    4. draw
    5. unbind shader
*/

class Shader
{
public:
    Shader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
    bool Compile();
    void Bind();
    void SetUniformMat4(std::string_view uniformName, const glm::mat4& uniformValue);
    void SetUniformVec3(std::string_view uniformName, const glm::vec3& uniformValue);
    void SetUniformVec4(std::string_view uniformName, const glm::vec4& uniformValue);
    void UnBind();
    void PrintErrorLog();
private:
    std::stringstream mError;
    std::string mVertexShaderPath, mFragmentShaderPath;
    GLuint mProgram = 0;

    static GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile, std::stringstream& errLog);
    static GLuint LoadShader(GLenum eShaderType, const std::string &strFilename, std::stringstream& errLog);
    static GLuint CreateProgram(const std::vector<GLuint> &shaderList, std::stringstream& errLog);
};