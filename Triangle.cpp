#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderManager.h"
#include "Shader.h"
#include "CompilationResult.h"

int main(void) {
    printf("Hi!\n");
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] ={
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    Shader vertex("../shaders/simple.vert", GL_VERTEX_SHADER);
    Shader fragment("../shaders/simple.frag", GL_FRAGMENT_SHADER);
    ShaderManager shaderManager = ShaderManager();
    shaderManager.add(vertex);
    shaderManager.add(fragment);

    CompilationResult shaderCompilationResult = shaderManager.compileShaders();

    if (shaderCompilationResult.status == CompilationResult::ERROR) {
        printf("%s \n", shaderCompilationResult.fileName.c_str());
        printf("%s \n", shaderCompilationResult.errorMessage.c_str());
        return -1;
    }

    shaderManager.link();

    CompilationResult linkResult = shaderManager.checkResults();
    if (linkResult.status == CompilationResult::ERROR) {
        printf("%s \n", linkResult.errorMessage.c_str());
        return -1;
    }

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
            );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f); // Changes for each model !
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    // Get a handle for our "MVP" uniform.
    // Only at initialisation time.
    GLuint MatrixID = glGetUniformLocation(shaderManager.getShaderProgramId(), "MVP");

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (g_vertex_buffer_data), &g_vertex_buffer_data, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderManager.getShaderProgramId());

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3, // size
                GL_FLOAT, // type
                GL_FALSE, // normalized?
                0, // stride
                (void*) 0 // array buffer offset
                );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glDisableVertexAttribArray(0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(shaderManager.getShaderProgramId());
    glDeleteVertexArrays(1, &VertexArrayID);

    glfwTerminate();
    return 0;
}
