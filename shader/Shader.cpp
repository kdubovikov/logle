#include <vector>

#include "Shader.h"

Shader::Shader(std::string path, GLenum shaderType) :
shaderType(shaderType),
path(path) {
    std::ifstream shaderFile(path, std::ios::in);
    
    if (shaderFile.is_open()) {
        std::string line = "";
        while (getline(shaderFile, line)) {
            code += "\n" + line;
        }

        shaderFile.close();
    } else {
        printf("An error has occured while opening shader file %s...\n", path.c_str());
    }
}

CompilationResult Shader::compile() {
    const char* pcode = code.c_str();

    shaderId = glCreateShader(shaderType);
    printf("Compiling shader - %d\n", shaderId);
    glShaderSource(shaderId, 1, &pcode, NULL);
    glCompileShader(shaderId);
    return checkResults();
}

GLuint Shader::getShaderId() {
    return shaderId;
}

CompilationResult Shader::checkResults() {
    CompilationResult result = {result.OK};
    GLint glResult = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &glResult);

    int logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    char* logMessageArr = new char[logLength + 1];
    glGetShaderInfoLog(shaderId, logLength, NULL, logMessageArr);

    if (glResult) {
        printf("All is ok...\n");
        return CompilationResult{CompilationResult::OK, path};
    } else {
        printf("%s \n", logMessageArr);
        logMessage.assign(logMessageArr, logLength);
        return CompilationResult{CompilationResult::ERROR, path, logMessage};
    }
}
