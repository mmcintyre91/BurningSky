#version 330 core

out vec4 FragColor;

uniform float u_Time;

void main()
{
	float g = 0.5 + 0.5 * sin(u_Time);
	FragColor = vec4(0.2, g, 0.9, 1.0);
}