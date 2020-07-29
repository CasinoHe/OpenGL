#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <filesystem>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

float vertices[] = {
  -0.5f, -0.5f, 0.0f, 
  0.5f, -0.5f, 0.0f,
  0.0f, 0.5f, 0.0f
};

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

GLFWwindow *create_window()
{
  GLFWwindow *window = glfwCreateWindow(800, 600, "Trialble", NULL, NULL);
  if (NULL == window)
  {
    glfwTerminate();
    return window;
  }

  return window;
}

void process_input(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

std::string get_shader_source(std::string filename)
{
  if (!std::filesystem::exists(filename))
  {
    return std::string("");
  }

  std::ifstream ifs;
  ifs.open(filename, std::ios::in);
  if (!ifs.is_open())
  {
    return std::string("");
  }

  ifs.seekg(std::ios::end);
  std::size_t length = ifs.tellg();
  ifs.seekg(std::ios::beg);

  std::string shader_source((std::istream_iterator<char>(ifs)),
                            std::istream_iterator<char>());

  return shader_source;
}


void backend(GLFWwindow *window)
{
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);


  std::string vertex_shader_source(get_shader_source("vertex_shader.glsl"));
  const char *p_shader_source = vertex_shader_source.data();

  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &p_shader_source, NULL);
  glCompileShader(vertex_shader);

  std::string fragment_shader_source(get_shader_source("fragment_shader.glsl"));
  p_shader_source = fragment_shader_source.data();

  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &p_shader_source, NULL);
  glCompileShader(fragment_shader);

  p_shader_source = NULL;

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glUseProgram(shader_program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  while (!glfwWindowShouldClose(window))
  {
    process_input(window);

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shader_program);

  glfwTerminate();
  return;
}

void ui_thread()
{
  GLFWwindow *window = create_window();
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

  backend(window);
}

int main()
{
  init_glfw();

  std::thread t(ui_thread);
  t.join();

  return 0;
}