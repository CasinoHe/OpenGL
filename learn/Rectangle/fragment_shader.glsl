#version 330 core
out vec4 frag_color;

in vec4 our_color;
// uniform vec4 our_color;

void main()
{
    frag_color = our_color;
}