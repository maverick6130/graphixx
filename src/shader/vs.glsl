#version 330

uniform mat4 mvp;
in vec4 vp;

void main () 
{
  gl_Position = mvp*vp;
}