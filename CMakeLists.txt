cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(opengl-tutorials)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(core)
add_subdirectory(shader)
include_directories(core shader ${GLFW_INCLUDE_DIRS})

add_executable(opengl-tutorials opengl-tutorials.cpp)
target_link_libraries(opengl-tutorials shader core ${GLFW_STATIC_LIBRARIES})
