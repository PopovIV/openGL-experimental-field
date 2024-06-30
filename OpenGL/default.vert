// Vertex Shader source code

#version 330 core
// shader input
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

// shader output
out vec3 color;
out vec2 texCoord;
out vec3 wPos;
out vec3 Normal;

// Matrix stuff
uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
   wPos = vec3(model * vec4(aPos, 1.0));
   gl_Position = camMatrix * vec4(wPos, 1.0);
   color = aColor;
   texCoord = aTex;
   Normal = normalize(vec3(model * vec4(aNormal, 1.0)));
}
