// Fragment Shader source code

#version 330 core
// Shader output
out vec4 FragColor;

// Shader input
in vec3 color;
in vec2 texCoord;
in vec3 wPos;
in vec3 Normal;

uniform sampler2D tex0;
// Light stuff
uniform vec3 camPos;
uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
   float ambient = 0.20f;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - wPos);

    float diffuse = max(dot(normal, lightDir), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDir = normalize(camPos - wPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
    float specular = specAmount * specularLight;

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}
