#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <ios>
#include <fstream>
#include <string>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "abstract_result.h"

class Shader: public AbstractResult
{
private:
    std::string code;

    GLenum shaderType;
    GLuint shaderId;

public:
    Shader(const char* path);
    void compile(GLenum shaderType);
    GLuint getShaderId();
    virtual bool checkResults();
    ~Shader();
};

#endif
