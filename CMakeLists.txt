cmake_minimum_required(VERSION 3.20)

project(triangle)

add_compile_definitions(PROJECT_PATH="${CMAKE_SOURCE_DIR}")

add_subdirectory(src/opengl)
add_subdirectory(src/vulkan)
