#opengl-tutorials

## Description
This is an [OpenGL tutorials](opengl-tutorial.org) implementation with attempt of making a simple lightweight rendering engine which can be used to create tech demos.

## Compilation
- GLFW library have to be installed in your system. I will migrate to static library dependency later. For Ubuntu:
```
> sudo apt-get install libglfw3-dev
```
- Also, you will need to build [SOIL2](https://bitbucket.org/SpartanJ/soil2) library and place it into `lib` directory.
- To compile this project you will need to run CMake.
```
> cmake .
> make
```
