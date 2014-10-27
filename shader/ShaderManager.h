#pragma once

#include <vector>
#include <functional>
#include "AbstractResult.h"
#include "CompilationResult.h"
#include "Shader.h"

class ShaderManager {
private:
    std::vector<std::reference_wrapper<Shader>> shaders;
    GLuint shaderProgramId;
public:
    void add(Shader& shader);
    CompilationResult compileShaders();
    void link();
    CompilationResult checkResults();
    GLuint getShaderProgramId();
    ~ShaderManager();
};
