cmake_minimum_required(VERSION 3.14.0)

project(OpenGL)

option(COMPILE_START_WINDOWS ON)

set(cmake_export_compile_commands True)
set(OPENGL_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(GLAD_SRC_FILE ${OPENGL_ROOT_DIRECTORY}/glad/src/glad.c)
include_directories(${OPENGL_ROOT_DIRECTORY}/glad/include)
include_directories(${OPENGL_ROOT_DIRECTORY}/glfw/include)

add_subdirectory(${OPENGL_ROOT_DIRECTORY}/glfw)
add_subdirectory(${OPENGL_ROOT_DIRECTORY}/learn/StartWindow)
add_subdirectory(${OPENGL_ROOT_DIRECTORY}/learn/Triangle)
add_subdirectory(${OPENGL_ROOT_DIRECTORY}/learn/Rectangle)
add_subdirectory(${OPENGL_ROOT_DIRECTORY}/learn/Vertices)