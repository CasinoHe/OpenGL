#version 330 core

out vec4 fragment_color;
in vec4 our_color;

void main()
{
  fragment_color = our_color;
}