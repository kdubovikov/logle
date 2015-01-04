# Lightweight OpenGL Engine

## Description
This is an [OpenGL tutorials](opengl-tutorial.org) implementation with attempt of making a simple lightweight rendering engine which can be used to create tech demos.

## Branches
This project uses [Git Flow](http://danielkummer.github.io/git-flow-cheatsheet/) branching model. The main development branch is `develop`. Releases are pushed into `master`.

## Compilation
- You will need to build [SOIL2](https://bitbucket.org/SpartanJ/soil2) library and place it into `lib` directory.
- To compile this project you will need to run CMake.

## Examples
Currently there is only one example of LOGLE usage. See `Example.cpp` at the root of the repository.

```
> cmake .
> make
```
