#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;

uniform mat4 u_Model;
uniform mat4 u_VP;

out vec3 aNormal;
out vec3 FragPos;

void main()
{
	aNormal = vec3(u_Model * vec4(Normal, 0.0f));
	vec4 worldPos = u_Model * vec4(Pos, 1.0f);
	FragPos = vec3(worldPos);
	gl_Position = u_VP * worldPos;
}