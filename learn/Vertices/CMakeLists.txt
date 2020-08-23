cmake_minimum_required(VERSION 3.14.0)

project(Vertices)

set(VERTICES_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(VERTICES_SOURCE_FILES
    ${GLAD_SRC_FILE}
    ${VERTICES_ROOT_DIR}/main.cpp
    ${VERTICES_ROOT_DIR}/ui_thread.cpp
    ${VERTICES_ROOT_DIR}/shader_util.cpp
)

include_directories(${OPENGL_ROOT_DIRECTORY}/glad/include)
include_directories(${OPENGL_ROOT_DIRECTORY}/glfw/include)

add_executable(${PROJECT_NAME} ${VERTICES_SOURCE_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw opengl32)
else ()
    target_link_libraries(${PROJECT_NAME} glfw GL X11 pthread Xrandr Xi dl)
endif (WIN32)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${VERTICES_ROOT_DIR}/fragment_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/Debug
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${VERTICES_ROOT_DIR}/vertex_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/Debug
)