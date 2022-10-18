#include <shader.h>
#include <utils.h>

#include <vector>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

GLuint Shader::CreateShader(GLenum eShaderType, const std::string &strShaderFile, std::stringstream& errLog)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch (eShaderType)
        {
        case GL_VERTEX_SHADER:
            strShaderType = "vertex";
            break;
        case GL_GEOMETRY_SHADER:
            strShaderType = "geometry";
            break;
        case GL_FRAGMENT_SHADER:
            strShaderType = "fragment";
            break;
        }

        errLog << "Compile failure in " << strShaderType << " shader:" << std::endl
                  << strInfoLog << std::endl;
        delete[] strInfoLog;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint Shader::LoadShader(GLenum eShaderType, const std::string &strFilename, std::stringstream& errLog)
{
    std::ifstream shaderFile(strFilename.c_str());
    if (!shaderFile.is_open())
        throw std::runtime_error("Cannot find file: " + strFilename);

    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();

    try
    {
        return CreateShader(eShaderType, shaderData.str(), errLog);
    }
    catch (std::exception &e)
    {
        errLog << e.what() << std::endl;
        return 0;
    }
}

GLuint Shader::CreateProgram(const std::vector<GLuint> &shaderList, std::stringstream& errLog)
{
    GLuint program = glCreateProgram();

    for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glAttachShader(program, shaderList[iLoop]);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        errLog << "GLSL Linker failure: " << strInfoLog << std::endl;
        delete[] strInfoLog;
        glDeleteProgram(program);
        return 0;
    }

    for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glDetachShader(program, shaderList[iLoop]);

    return program;
}

Shader::Shader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath) : 
mVertexShaderPath(vertexShaderPath), mFragmentShaderPath(fragmentShaderPath) {}

bool Shader::Compile()
{
    GLuint vs = Shader::LoadShader(GL_VERTEX_SHADER, mVertexShaderPath, mError);
    if (!vs)
        return false;

    GLuint fs = Shader::LoadShader(GL_FRAGMENT_SHADER, mFragmentShaderPath, mError);
    if (!fs)
        return false;

    mProgram = Shader::CreateProgram({vs, fs}, mError);
    if (!mProgram)
        return false;
    
    return true;
}

void Shader::Bind()
{
    THROW_IF(!mProgram, (mError.str().size() ? mError.str() : "Compile shader before binding!"));
    glUseProgram(mProgram);
}

void Shader::UnBind()
{
    glUseProgram(0);
}

void Shader::SetUniformMat4(std::string_view uniformName, const glm::mat4& uniformValue)
{
    GLuint loc = glGetUniformLocation(mProgram, uniformName.data());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(uniformValue));
}

void Shader::SetUniformVec3(std::string_view uniformName, const glm::vec3& uniformValue)
{
    GLuint loc = glGetUniformLocation(mProgram, uniformName.data());
    glUniform3fv(loc, 1, glm::value_ptr(uniformValue));
}

void Shader::SetUniformVec4(std::string_view uniformName, const glm::vec4& uniformValue)
{
    GLuint loc = glGetUniformLocation(mProgram, uniformName.data());
    glUniform4fv(loc, 1, glm::value_ptr(uniformValue));
}

void Shader::PrintErrorLog()
{
    std::cout << mError.str() << std::endl;
}