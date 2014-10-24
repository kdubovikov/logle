#pragma once

#include <vector>
#include <functional>
#include "abstract_result.h"
#include "compilation_result.h"
#include "shader.h"

class ShaderManager
{
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
