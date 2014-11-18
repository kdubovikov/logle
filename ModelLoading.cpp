#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include "glfw/glfw3.h"

#include "Shader.h"
#include "StaticMesh.h"
#include "Camera.h"
#include "Scene.h"
#include "InputManager.h"

int main(void) {
    printf("Hi!\n");
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Model loading", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    std::string vshaderFile("./rsc/shaders/textured/textured.vert");
    std::string fshaderFile("./rsc/shaders/textured/textured.frag");
    Shader vshader(vshaderFile, GL_VERTEX_SHADER);
    Shader fshader(fshaderFile, GL_FRAGMENT_SHADER);
    
    StaticMesh cube("./rsc/models/suzanne.obj", vshader, fshader);
    std::string texturePath("./rsc/models/uvmap.DDS");
    cube.prepareDDSTextureCustom(texturePath);
    
    std::unique_ptr<Camera> camera(new Camera());
    glm::vec3 trVec(0, 0, 5);
    camera.get()->setCameraPosition(trVec);
    std::unique_ptr<InputManager> inputManager(new InputManager(window));
    
    Scene scene;
    scene.setCamera(camera);
    scene.setInputManager(inputManager);
    scene.addObject(cube);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.render();

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
