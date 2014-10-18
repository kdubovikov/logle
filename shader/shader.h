#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <ios>
#include <fstream>
#include <string>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

class Shader {
private:
  std::string code;
  std::string errorMessage;

  GLenum shaderType;
  GLuint shaderId;

public:
  Shader(const char* path);
  bool compile(GLenum shaderType);
  std::string getErrorMessage();
  ~Shader();
};

#endif
