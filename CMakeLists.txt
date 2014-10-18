cmake_minimum_required(VERSION 2.8)
project (glfw_test)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(glfw)
include_directories(glfw/include)

add_executable(glfw_test glfw_test.cpp)
target_link_libraries(glfw_test glfw ${GLFW_LIBRARIES})