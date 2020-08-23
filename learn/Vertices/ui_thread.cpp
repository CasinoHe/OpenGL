#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ui_thread.h"
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
  init_glfw();

  static float vertices[] = {
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,   // top right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom right
  };

  static int indices[] = {
    0, 1, 2,
    1, 2, 3,
  };

  GLFWwindow *window = glfwCreateWindow(800, 600, "Vertices", NULL, NULL);
  if (NULL == window)
  {
    std::cout << "Cannot create window" << std::endl;
    return;
  }

  glfwMakeContextCurrent(window);
  if (init_glad() < 0)
  {
    std::cout << "Cannot init glad " << std::endl;
    glfwTerminate();
    return;
  }

  unsigned int VBO, VAO, EBO;
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &VAO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  Shaders::CShaderProgram shader_program;
  if (!shader_program.set_fragment_shader(std::string("fragment_shader.glsl")))
  {
    return;
  }
  if (!shader_program.set_vertex_shader(std::string("vertex_shader.glsl")))
  {
    return;
  }
  if (!shader_program.compile_program())
  {
    return;
  }

  unsigned int program = shader_program.get_program_id();

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glfwSwapBuffers(window);
    glUseProgram(program);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  glfwTerminate();
}