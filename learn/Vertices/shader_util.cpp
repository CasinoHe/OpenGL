#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shader_util.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Shaders
{
  CShaderProgram::CShaderProgram() : m_program_id(0), m_vertex_shader_path(""), m_fragment_shader_path("")
  {
  }

  std::string CShaderProgram::load_shader_source(std::string &filepath)
  {
    if (!std::filesystem::exists(filepath))
    {
      std::cerr << "- Fatal - Cannot find shader source file: " << filepath << std::endl;
      return std::string("");
    }

    std::ifstream ifs;
    ifs.open(filepath, std::ios::in);

    if (!ifs.is_open())
    {
      std::cerr << "- Fatal - Cannot open file: " << filepath << std::endl;
      return std::string("");
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    
    return ss.str();
  }

  bool CShaderProgram::set_vertex_shader(std::string &filepath)
  {
    if (!std::filesystem::exists(filepath))
    {
      std::cerr << "- Fatal - Cannot find vertex shader path: " << filepath << std::endl;
      return false;
    }
    else
    {
      m_vertex_shader_path = filepath;
      return true;
    }
  }

  bool CShaderProgram::set_fragment_shader(std::string &filepath)
  {
    if (!std::filesystem::exists(filepath))
    {
      std::cerr << "- Fatal - Cannot find fragment shader path: " << filepath << std::endl;
      return false;
    }
    else
    {
      m_fragment_shader_path = filepath;
      return true;
    }
  }

  bool CShaderProgram::compile_program()
  {
    if (m_vertex_shader_path.empty())
    {
      std::cerr << "- Fatal - Cannot compile program while vertex shader is none" << std::endl;
      return false;
    }

    if (m_fragment_shader_path.empty())
    {
      std::cerr << "- Fatal - Cannot compile program while fragment shader is none" << std::endl;
      return false;
    }

    // compile vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_shader_source(load_shader_source(m_vertex_shader_path));
    if (vertex_shader_source.empty())
    {
      std::cerr << "Cannot read vertex shader source" << std::endl;
      return false;
    }
    const char *pshader = &vertex_shader_source[0];
    glShaderSource(vertex_shader, 1, &pshader, NULL);
    glCompileShader(vertex_shader);
    if (!is_shader_compile_succeed(vertex_shader))
    {
      return false;
    }

    pshader = NULL;

    // compile fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragment_shader_source(load_shader_source(m_fragment_shader_path));
    if (fragment_shader_source.empty())
    {
      std::cerr << "Cannot read fragment shader source" << std::endl;
      return false;
    }
    pshader = &fragment_shader_source[0];
    glShaderSource(fragment_shader, 1, &pshader, NULL);
    glCompileShader(fragment_shader);
    if (!is_shader_compile_succeed(fragment_shader))
    {
      return false;
    }

    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader);
    glAttachShader(m_program_id, fragment_shader);
    glLinkProgram(m_program_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return true;
  }

  bool CShaderProgram::is_shader_compile_succeed(unsigned int &shader)
  {
    int succeed;
    char error_log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &succeed);
    if (succeed)
    {
      return true;
    }
    else
    {
      glGetShaderInfoLog(shader, 512, NULL, error_log);
      std::cerr << "Compile Shader failed. Message: " << error_log << std::endl;
      return false;
    }
  }

  unsigned int CShaderProgram::get_program_id()
  {
    return m_program_id;
  }
} // namespace Shaders