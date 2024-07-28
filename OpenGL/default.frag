// Fragment Shader source code

#version 330 core
// Shader output
out vec4 FragColor;

// Shader input
in vec3 wPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
// Light stuff
uniform vec3 camPos;
uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
   float ambient = 0.20f;

    vec3 normal = normalize(Normal);
    vec3 lightDir = lightPos - wPos;
    float lightDist = length(lightDir);
    lightDir /= lightDist;

    float atten = clamp(1.0 / (lightDist * lightDist), 0.0f, 1.0f);

    float diffuse = max(dot(normal, lightDir), 0.0f) * atten;

    float specularLight = 0.50f;
    vec3 viewDir = normalize(camPos - wPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
    float specular = specAmount * specularLight * atten;

    FragColor = texture(diffuse0, texCoord) * lightColor * (diffuse + ambient + specular);
}
