cmake_minimum_required(VERSION 3.14.0)

project(Vertices)

set(VERTICES_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(VERTICES_SOURCE_FILES
    ${GLAD_SRC_FILE}
    ${VERTICES_ROOT_DIR}/main.cpp
    ${VERTICES_ROOT_DIR}/shader_util.cpp
)

add_executable(${PROJECT_NAME} ${VERTICES_SOURCE_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw opengl32)
else ()
    target_link_libraries(${PROJECT_NAME} glfw GL X11 pthread Xrandr Xi dl)
endif (WIN32)