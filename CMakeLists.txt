cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -std=c++11")
project(opengl-tutorials)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(core)
add_subdirectory(shader)
add_subdirectory(render)
add_subdirectory(input)
include_directories(core shader render input ${GLFW_INCLUDE_DIRS})

add_executable(triangle Triangle.cpp)
target_link_libraries(triangle shader core render ${GLFW_STATIC_LIBRARIES})

add_executable(colored_cube ColoredCube.cpp)
target_link_libraries(colored_cube shader core render ${GLFW_STATIC_LIBRARIES})

add_executable(textured_cube TexturedCube.cpp)
target_link_libraries(textured_cube shader core render ${GLFW_STATIC_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/libsoil2.a)

add_executable(input_test InputTest.cpp)
target_link_libraries(input_test shader core render input ${GLFW_STATIC_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/libsoil2.a)

add_executable(model_loader_test ModelLoading.cpp)
target_link_libraries(model_loader_test shader core render input ${GLFW_STATIC_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/libsoil2.a)