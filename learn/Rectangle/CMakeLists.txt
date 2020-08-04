cmake_minimum_required(VERSION 3.14.0)

project(Rectangle)

set(RECTANGLE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RECTANGLE_SOURCE 
    ${GLAD_SRC_FILE}
    ${RECTANGLE_ROOT_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${RECTANGLE_SOURCE})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw opengl32)
else ()
    target_link_libraries(${PROJECT_NAME} glfw GL X11 pthread Xrandr Xi dl)
endif (WIN32)