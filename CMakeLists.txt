cmake_minimum_required(VERSION 3.14.0)

project(OpenGL)

option(COMPILE_START_WINDOWS ON)

set(cmake_export_compile_commands True)
set(OPENGL_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(${OPENGL_ROOT_DIRECTORY}/glfw)
add_subdirectory(${OPENGL_ROOT_DIRECTORY}/learn/StartWindow)