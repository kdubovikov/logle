#include "shader.h"

Shader::Shader(const char* path) {
  std::ifstream shaderFile(path, std::ios::in);

  if (shaderFile.is_open()) {
    std::string line = "";
    while (getline(shaderFile, line)) {
      code += "\n" + line;
    }

    shaderFile.close();
  }
}

bool Shader::compile(GLenum shaderType) {
  this->shaderType = shaderType;
  const char* pcode = code.c_str();

  shaderId = glCreateShader(shaderType);
  glShaderSource(shaderId, 1, &pcode, NULL);
  glCompileShader(shaderId);

  GLint result;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

  int logLength;
  glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

  char* logMessage = new char[logLength];
  glGetShaderInfoLog(shaderId, logLength, NULL, &logMessage[0]);
  errorMessage.assign(logMessage, logLength);

  return result;
}

std::string Shader::getErrorMessage() {
    return errorMessage;
}

Shader::~Shader() {
    glDeleteShader(shaderId);
}
