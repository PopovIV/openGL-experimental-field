// Vertex Shader source code

#version 330 core
// shader input
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// shader output
out vec3 color;
out vec2 texCoord;

// Set ups scale of vertices
uniform float scale;

// Matrix stuff
uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
   gl_Position = camMatrix * model * vec4(aPos, 1.0);
   color = aColor;
   texCoord = aTex;
}
