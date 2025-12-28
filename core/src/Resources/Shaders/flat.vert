#version 460 core

layout (location = 0) in vec3 Pos;
uniform mat4 u_Model;
uniform mat4 u_VP;

void main()
{
	gl_Position = u_VP * u_Model * vec4(Pos, 1.0f);
}