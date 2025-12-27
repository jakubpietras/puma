#version 460 core

uniform mat4 u_Model;
uniform mat4 u_VP;

out vec3 v_Color;

const vec3 positions[6] = vec3[](
    vec3(0.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0),
    vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0)
);

const vec3 colors[6] = vec3[](
    vec3(0.3, 0.0, 0.0), vec3(1.0, 0.0, 0.0),
    vec3(0.0, 0.3, 0.0), vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 0.3), vec3(0.0, 0.0, 1.0)
);

void main()
{
	vec3 localPos = positions[gl_VertexID];
    v_Color = colors[gl_VertexID];
    gl_Position = u_VP * u_Model * vec4(localPos, 1.0);
}