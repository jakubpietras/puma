#version 460 core

uniform vec3 u_CameraPos;
uniform vec3 u_Color;

in vec3 aNormal;
in vec3 FragPos;

out vec4 FragColor;

const vec3 lightColor = {1, 1, 1};

void main()
{
	vec3 norm = normalize(aNormal);
	vec3 lightDir = normalize(u_CameraPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 ambient = 0.4 * lightColor;
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * u_Color;
	FragColor = vec4(result, 1.0);
}