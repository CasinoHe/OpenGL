#include <iostream>
#include <thread>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

static float vertices[] = {
    -0.5f, 0.5f, 0.0f,  // top left
    0.5f, 0.5f, 0.0f,   // top right
    -0.5f, -0.5f, 0.0f, // bottom left
    0.5f, -0.5f, 0.0f,  // bottom right
};
static unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3,
};

void init_glfw()
{
  glfwInit();
  glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int init_glad()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

void process_input(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
  else
  {
    glfwSetWindowShouldClose(window, false);
  }
}

std::string get_shader_source(std::string &path)
{
  if (!std::filesystem::exists(path))
  {
    std::cout << "Cannot find shader source file " << path << std::endl;
    return std::string("");
  }

  std::ifstream ifs;
  ifs.open(path, std::ios::in);
  if (!ifs.is_open())
  { 
    std::cout << "Cannot open shader file " << path << std::endl;
    return std::string("");
  }

  std::stringstream shader_stream;
  shader_stream << ifs.rdbuf();
  ifs.close();

  return shader_stream.str();
}

void ui_thread()
{
  init_glfw();

  GLFWwindow *window = glfwCreateWindow(800, 600, "Rectangle", NULL, NULL);

  if (NULL == window)
  {
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);
  init_glad();

  unsigned int VBO, VAO, EBO;
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), NULL);
  glEnableVertexAttribArray(0);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBindVertexArray(0);

  std::string vertex_shader_source(get_shader_source(std::string("vertex_shader.glsl")));
  const char *p_source = &vertex_shader_source[0];

  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &p_source, NULL);
  glCompileShader(vertex_shader);

  int success;
  char err_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  { 
    glGetShaderInfoLog(vertex_shader, 512, NULL, err_log);
    std::cout << "Compile vertex shader error: " << err_log << std::endl;
    return;
  }

  std::string fragment_shader_source(get_shader_source(std::string("fragment_shader.glsl")));
  p_source = &fragment_shader_source[0];

  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &p_source, NULL);
  glCompileShader(fragment_shader);


  unsigned int program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glfwSwapBuffers(window);

    glUseProgram(program);
    // float time_value = static_cast<float>(glfwGetTime());
    // float green_value = static_cast<float>(sin(time_value) / 2.0f + 0.5);
    // int vertex_location = glGetUniformLocation(program, "our_color");
    // glUniform4f(vertex_location, 0.0f, green_value, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    process_input(window);
  }

  glfwTerminate();
}

int main()
{
  std::shared_ptr<std::thread> t = std::make_shared<std::thread>(ui_thread);
  if (t->joinable())
  {
    t->join();
  }
  return 0;
}