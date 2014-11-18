#include "ShaderManager.h"

void ShaderManager::add(Shader& shader) {
    shaders.push_back(shader);
}

void ShaderManager::addUniform(const std::string& uniformName, const glm::mat4& matrix) {
    uniformManager.get()->addMatrix4(uniformName, matrix);
}

void ShaderManager::addUniform(const std::string& uniformName, const glm::vec3& vector) {
    uniformManager.get()->addVector3(uniformName, vector);    
}

void ShaderManager::addUniform(const std::string& uniformName, GLint textureNumber) {
    uniformManager.get()->addSampler(uniformName, textureNumber);
}

void ShaderManager::addUniform(const std::string& uniformName, GLfloat number) {
    uniformManager.get()->addFloat(uniformName, number);
}

GLuint ShaderManager::getUniformId(const std::string& uniformName) {
    return uniformManager.get()->getUniformId(uniformName);
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

CompilationResult ShaderManager::link() {
    shaderProgramId = glCreateProgram();

    for (Shader& shader : shaders) {
        glAttachShader(shaderProgramId, shader.getShaderId());
    }

    glLinkProgram(shaderProgramId);
    
    CompilationResult result = checkLinkResults();
    if (result.status == CompilationResult::OK) {
        UniformManager* manager = new UniformManager(shaderProgramId);
        uniformManager = std::unique_ptr<UniformManager>(manager);
    }
    
    return result;
}

CompilationResult ShaderManager::checkLinkResults() {
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
        printf("Error - %s\n", logMessageArr);
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


