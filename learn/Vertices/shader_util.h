#pragma once

#include <iostream>
#include <string>

namespace Shaders
{
  class CShaderProgram
  {
  public:
    CShaderProgram();

  public:
    CShaderProgram(CShaderProgram &) = delete;

    unsigned int get_program_id();
    bool set_vertex_shader(std::string &filepath);
    bool set_fragment_shader(std::string &filepath);
    bool compile_program();

  private:
    std::string load_shader_source(std::string &filepath);
    bool is_shader_compile_succeed(unsigned int &shader);

  private:
    unsigned int m_program_id;
    std::string m_vertex_shader_path;
    std::string m_fragment_shader_path;
  };
}; // namespace Shaders