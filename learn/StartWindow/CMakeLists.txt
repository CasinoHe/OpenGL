cmake_minimum_required(VERSION 3.14.0)

project(StartWindows)

set(START_WINDOWS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_FILES
    ${START_WINDOWS_ROOT_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw opengl32)
else ()
    target_link_libraries(${PROJECT_NAME} glfw GL X11 pthread Xrandr Xi dl)
endif (WIN32)