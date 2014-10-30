#include "TexturedGeometry.h"

TexturedGeometry::TexturedGeometry(const size_t bufferSize, Shader& vertexShader, Shader& fragmentShader) :
shaderManager(ShaderManager()),
bufferSize(bufferSize) {
    shaderManager.add(vertexShader);
    shaderManager.add(fragmentShader);
}

void TexturedGeometry::prepareShaders() {
    // TODO: add some kind of AbstractResult class and return status
    CompilationResult shaderCompilationResult = shaderManager.compileShaders();

    if (shaderCompilationResult.status == CompilationResult::ERROR) {
        printf("%s \n", shaderCompilationResult.fileName.c_str());
        printf("%s \n", shaderCompilationResult.errorMessage.c_str());
        return;
    }

    shaderManager.link();

    CompilationResult linkResult = shaderManager.checkResults();
    if (linkResult.status == CompilationResult::ERROR) {
        printf("%s \n", linkResult.errorMessage.c_str());
        return;
    }
    
    textureUniformId = glGetUniformLocation(shaderManager.getShaderProgramId(), "textureSampler");
}

void TexturedGeometry::prepareBuffers(const std::vector<GLfloat>& vertexBufferData, const std::vector<GLfloat>& uvBufferData) {
    vertexBufferId = prepareBuffer(vertexBufferData);
    uvBufferId = prepareBuffer(uvBufferData);
}

void TexturedGeometry::prepareTexture(const std::string& imagePath) {
    texture.load(imagePath);
    texture.prepareTexture();
}


GLuint TexturedGeometry::prepareBuffer(const std::vector<GLfloat>& bufferData) {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(GLfloat), bufferData.data(), GL_STATIC_DRAW);
    
    return bufferId;
}

void TexturedGeometry::render() {
    glUseProgram(shaderManager.getShaderProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glUniform1i(textureUniformId, 0);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    // TODO: abstract away buffer sizes, change from 3 to 2 breaks second tutorial
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glDrawArrays(GL_TRIANGLES, 0, bufferSize * 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

ShaderManager& TexturedGeometry::getShaderManager() {
    return shaderManager;
}

TexturedGeometry::~TexturedGeometry() {
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &uvBufferId);
}