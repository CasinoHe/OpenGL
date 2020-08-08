#include <iostream>
#include <thread>
#include <memory>

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

  const char *vertex_shader_source = "#version 330 core \n\
  layout (location=0) in vec3 pos; \n\
  out vec4 vertex_color; \n\
  void main() \n\
  { \n \
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); \n\
    vertex_color = vec4(0.1, 0.0, 1.0, 1.0); \n\
  }";

  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  const char *fragment_shader_soure = "#version 330 core \n\
  out vec4 FragColor; \n\
  in vec4 vertex_color; \n\
  uniform vec4 our_color;\n\
  void main() \n\
  {\n\
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n\
    // FragColor = vertex_color; \n\
    FragColor = our_color; \n\
  }";

  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_soure, NULL);
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
    float time_value = static_cast<float>(glfwGetTime());
    float green_value = static_cast<float>(sin(time_value) / 2.0f + 0.5);
    int vertex_location = glGetUniformLocation(program, "our_color");
    glUniform4f(vertex_location, 0.0f, green_value, 0.0f, 1.0f);

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