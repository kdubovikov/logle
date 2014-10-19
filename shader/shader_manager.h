#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <vector>
#include "shader.h"

class ShaderManager
{
    private:
        std::string linkLog;
        std::vector<Shader> shaders;
        GLuint shaderProgramId;
    public:
        void add(Shader& shader);
        void link();
        bool checkResults();
        GLuint getShaderProgramId();
        ~ShaderManager();
};

#endif // SHADER_MANAGER_H
