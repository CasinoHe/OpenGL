cmake_minimum_required(VERSION 3.14.0)

project(Triangle)

set(TRIANGLE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TRIANGLE_SRC_FILES
    ${GLAD_SRC_FILE}
    ${TRIANGLE_ROOT_DIR}/main.cpp
)

file(COPY ${TRIANGLE_ROOT_DIR}/vertex_shader.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${TRIANGLE_ROOT_DIR}/fragment_shader.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

add_executable(${PROJECT_NAME} ${TRIANGLE_SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw opengl32)
else ()
    target_link_libraries(${PROJECT_NAME} glfw GL X11 pthread Xrandr Xi dl)
endif (WIN32)

# add_custom_command(
#     TARGET Triangle POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -e copy_if_different
#     ${TRIANGLE_ROOT_DIR}/vertex_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/Debug
# )

# add_custom_command(
#     TARGET Triangle POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -e copy_if_different
#     ${TRIANGLE_ROOT_DIR}/fragment_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/Debug
# )