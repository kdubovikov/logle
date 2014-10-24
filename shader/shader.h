#pragma once
#include <string>
#include <ios>
#include <fstream>
#include <string>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "compilation_result.h"

class Shader
{
private:
    std::string path;
    std::string code;
    std::string logMessage;
    GLenum shaderType;
    GLuint shaderId;
    
    CompilationResult checkResults();

public:
    Shader(const char* path, GLenum shaderType);
    CompilationResult compile();
    GLuint getShaderId();
};