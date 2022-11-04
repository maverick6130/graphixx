#version 330

uniform mat4 model_matrix, view_proj_matrix;
in vec4 vertex_pos;
in vec4 color;

void main () 
{
  gl_Position = view_proj_matrix * model_matrix * vertex_pos;
}