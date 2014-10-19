#include "shader.h"

Shader::Shader(const char* path)
{
    std::ifstream shaderFile(path, std::ios::in);

    if (shaderFile.is_open())
    {
        std::string line = "";
        while (getline(shaderFile, line))
        {
            code += "\n" + line;
        }

        shaderFile.close();
    }
}

void Shader::compile(GLenum shaderType)
{
    this->shaderType = shaderType;
    const char* pcode = code.c_str();

    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &pcode, NULL);
    glCompileShader(shaderId);
}

GLuint Shader::getShaderId()
{
    return shaderId;
}

bool Shader::checkResults()
{
    GLint result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    int logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    char* logMessageArr = new char[logLength];
    glGetShaderInfoLog(shaderId, logLength, NULL, &logMessageArr[0]);
    logMessage.assign(logMessageArr, logLength);

    return result;
}

Shader::~Shader()
{
    glDeleteShader(shaderId);
}
