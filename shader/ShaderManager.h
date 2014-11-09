#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "CompilationResult.h"
#include "Shader.h"
#include "UniformManager.h"

class ShaderManager {
private:
    GLuint shaderProgramId;
    std::vector<std::reference_wrapper<Shader>> shaders;
    std::unique_ptr<UniformManager> uniformManager;
    CompilationResult checkLinkResults();
public:
    void addUniform(const std::string& uniformName, const glm::mat4& matrix);
    void addUniform(const std::string& uniformName, const glm::vec3& vector);
    void addUniform(const std::string& uniformName, GLint textureNumber);
    GLuint getUniformId(const std::string& uniformName);
    void add(Shader& shader);
    CompilationResult compileShaders();
    CompilationResult link();
    GLuint getShaderProgramId();
    ~ShaderManager();
};
