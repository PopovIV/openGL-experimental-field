//Fragment Shader source code

#version 330 core
// shader output
out vec4 FragColor;

// shader input
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, texCoord);
}
