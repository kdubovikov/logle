#include "ShaderManager.h"

void ShaderManager::add(Shader& shader) {
    shaders.push_back(shader);
}

CompilationResult ShaderManager::compileShaders() {
    for (Shader& shader : shaders) {
        CompilationResult result = shader.compile();
        if (result.status == CompilationResult::ERROR) {
            return result;
        }
    }

    return CompilationResult{CompilationResult::OK};
}

void ShaderManager::link() {
    shaderProgramId = glCreateProgram();

    for (Shader& shader : shaders) {
        glAttachShader(shaderProgramId, shader.getShaderId());
    }

    glLinkProgram(shaderProgramId);
}

CompilationResult ShaderManager::checkResults() {
    GLint result = GL_FALSE;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &result);

    GLint logLength;
    glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &logLength);

    GLchar* logMessageArr = new GLchar[logLength + 1];
    glGetShaderInfoLog(shaderProgramId, logLength, NULL, logMessageArr);

    if (result) {
        printf("All is OK...\n");
        return CompilationResult{CompilationResult::OK};
    } else {
        std::string logMessage;
        logMessage.assign(logMessageArr, logLength);
        return CompilationResult{CompilationResult::ERROR, "", logMessage};
    }
}

GLuint ShaderManager::getShaderProgramId() {
    return shaderProgramId;
}

ShaderManager::~ShaderManager() {
    for (Shader shader : shaders) {
        glDeleteShader(shader.getShaderId());
    }
    
    glDeleteProgram(shaderProgramId);
}


