#pragma once

#include <vector>
#include <functional>

#include "CompilationResult.h"
#include "Shader.h"

class ShaderManager {
private:
    GLuint shaderProgramId;
    std::vector<std::reference_wrapper<Shader>> shaders;
public:
    void add(Shader& shader);
    CompilationResult compileShaders();
    void link();
    CompilationResult checkResults();
    GLuint getShaderProgramId();
    ~ShaderManager();
};
