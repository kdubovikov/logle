/* 
 * File:   UniformManager.cpp
 * Author: kdubovikov
 * 
 * Created on November 9, 2014, 2:45 AM
 */

#include <string>

#include "UniformManager.h"

UniformManager::UniformManager(const GLuint shaderProgramId) :
shaderProgramId(shaderProgramId) {
}

void UniformManager::addMatrix4(const std::string& uniformName, const glm::mat4& matrix) {
    GLuint uniformId = createUniform(uniformName);
    glUniformMatrix4fv(uniformId, 1, GL_FALSE, &matrix[0][0]);
}

void UniformManager::addVector3(const std::string& uniformName, const glm::vec3& vector) {
    GLuint uniformId = createUniform(uniformName);
    glUniform3f(uniformId, vector.x, vector.y, vector.z);
}

void UniformManager::addSampler(const std::string& uniformName, GLint number) {
    GLuint uniformId = createUniform(uniformName);
    glUniform1i(uniformId, number);
}


GLuint UniformManager::createUniform(const std::string& uniformName) {
    GLuint uniformId = glGetUniformLocation(shaderProgramId, uniformName.c_str());
    uniformIdMap[uniformName] = uniformId;
    return uniformId;
}

GLuint UniformManager::getUniformId(const std::string& uniformName) {
    if (uniformIdMap.count(uniformName) > 0) {
        return uniformIdMap[uniformName];
    } else {
        return -1;
    }
}



