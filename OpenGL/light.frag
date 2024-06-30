#version 330 core

// Shader output
out vec4 FragColor;

// Shader input
uniform vec4 lightColor;

void main()
{
	FragColor = lightColor;
}
