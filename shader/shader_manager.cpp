#include "shader_manager.h"

ShaderManager::~ShaderManager()
{
    for (Shader& shader : shaders)
    {
        shader.~Shader();
    }
}

void ShaderManager::add(Shader& shader)
{
    shaders.push_back(shader);
}

void ShaderManager::link()
{
    shaderProgramId = glCreateProgram();

    for (Shader& shader : shaders)
    {
        glAttachShader(shaderProgramId, shader.getShaderId());
    }

    glLinkProgram(shaderProgramId);
}

bool ShaderManager::checkResults()
{
    GLint result = GL_FALSE;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &result);


    GLint logLength;
    glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &logLength);

    char* logMessage = new char[logLength];
    glGetShaderInfoLog(shaderProgramId, logLength, NULL, &logMessage[0]);
    linkLog.assign(logMessage, logLength);

    return result;
}

GLuint ShaderManager::getShaderProgramId()
{
    return shaderProgramId;
}

