#include <iostream>
#include <thread>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader_util.h"

void init_glfw()
{
  glfwInit();
  glfwInitHint(GLFW_VERSION_MAJOR, 3);
  glfwInitHint(GLFW_VERSION_MINOR, 3);
  glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int init_glad()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    return -1;
  }

  return 0;
}

void ui_thread()
{
}

int main()
{
  init_glfw();

  std::shared_ptr<std::thread> t = std::make_shared<std::thread>(ui_thread);
  if (t->joinable())
  { 
    t->join();
  }

  return 0;
}