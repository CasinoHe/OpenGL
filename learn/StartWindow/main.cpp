#include <iostream>
#include <thread>
#include <chrono>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void init_glfw()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int init_glad()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to init GLAD!" << std::endl;
    return -1;
  }
  return 0;
}

void resize_windows_callback(GLFWwindow *windows, int width, int hight)
{
  glViewport(0, 0, width, hight);
}

GLFWwindow *create_windows()
{
  GLFWwindow *window = glfwCreateWindow(800, 600, "Hello", NULL, NULL);
  if (NULL == window)
  {
    std::cout << "Failed to create glfw window" << std::endl;
    glfwTerminate();
    return window;
  }
  return window;
}

void register_windows_callback(GLFWwindow *window)
{
  glViewport(0, 0, 800, 600);
  // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  // glClear(GL_COLOR_BUFFER_BIT);

  glfwSetFramebufferSizeCallback(window, resize_windows_callback);
}

void process_input(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

void backend(GLFWwindow *window)
{
  while (!glfwWindowShouldClose(window))
  {
    process_input(window);
    
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}

void ui_thread()
{
  GLFWwindow *window = create_windows();

  if (NULL == window)
  {
    return;
  }

  // make current context
  glfwMakeContextCurrent(window);

  if (init_glad() < 0)
  {
    glfwTerminate();
    return;
  }

  register_windows_callback(window);
  backend(window);

  glfwTerminate();
}

int main()
{
  init_glfw();

  std::thread t(ui_thread);
  t.join();

  return 0;
}