#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <vector>
#include "abstract_result.h"
#include "shader.h"

class ShaderManager: public AbstractResult
{
    private:
        std::vector<Shader> shaders;
        GLuint shaderProgramId;
    public:
        void add(Shader& shader);
        void link();
        virtual bool checkResults();
        GLuint getShaderProgramId();
        ~ShaderManager();
};

#endif // SHADER_MANAGER_H
