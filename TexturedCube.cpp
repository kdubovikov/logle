#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "StaticMesh.h"
#include "Camera.h"
#include "Scene.h"

int main(void) {
    printf("Hi!\n");
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Textured cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    std::vector<GLfloat> g_vertex_buffer_data = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    };

    // Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
    std::vector<GLfloat> g_uv_buffer_data = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.336024f, 1.0f-0.671877f,
        0.667969f, 1.0f-0.671889f,
        1.000023f, 1.0f-0.000013f,
        0.668104f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.000059f, 1.0f-0.000004f,
        0.335973f, 1.0f-0.335903f,
        0.336098f, 1.0f-0.000071f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.336024f, 1.0f-0.671877f,
        1.000004f, 1.0f-0.671847f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.668104f, 1.0f-0.000013f,
        0.335973f, 1.0f-0.335903f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.668104f, 1.0f-0.000013f,
        0.336098f, 1.0f-0.000071f,
        0.000103f, 1.0f-0.336048f,
        0.000004f, 1.0f-0.671870f,
        0.336024f, 1.0f-0.671877f,
        0.000103f, 1.0f-0.336048f,
        0.336024f, 1.0f-0.671877f,
        0.335973f, 1.0f-0.335903f,
        0.667969f, 1.0f-0.671889f,
        1.000004f, 1.0f-0.671847f,
        0.667979f, 1.0f-0.335851f
    };
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

//    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
//    glm::mat4 View = glm::lookAt(
//            glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
//            glm::vec3(0, 0, 0), // and looks at the origin
//            glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
//            );
//    glm::mat4 Model = glm::mat4(1.0f);
//    glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
//    
    std::string vshaderFile("../shaders/textured/textured.vert");
    std::string fshaderFile("../shaders/textured/textured.frag");
    Shader vshader(vshaderFile, GL_VERTEX_SHADER);
    Shader fshader(fshaderFile, GL_FRAGMENT_SHADER);
    
    StaticMesh cube(vshader, fshader);
    cube.prepareShaders();
    cube.prepareBuffers(3, g_vertex_buffer_data, 2, g_uv_buffer_data);
    
    std::string texturePath("../textures/numbers.tga");
    cube.prepareTexture(texturePath);
    
    Camera camera;
    glm::vec3 translateVector = glm::vec3(4, 3, -3);
    glm::vec3 lookVector = glm::vec3(0, 0, 0);
    camera.setCameraPosition(translateVector);
    camera.lookAt(lookVector);
    
    Scene scene;
    scene.setCamera(&camera);
    scene.addObject(cube);
    
    
    // Get a handle for our "MVP" uniform.
    // Only at initialisation time.
    //GLuint MatrixID = glGetUniformLocation(cube.getShaderManager().getShaderProgramId(), "MVP");
  
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //camera.applyTransformation();
        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        //cube.render();
        scene.render();

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

//    cube.~SimpleGeometry();
    glDeleteVertexArrays(1, &VertexArrayID);

    glfwTerminate();
    return 0;
}
