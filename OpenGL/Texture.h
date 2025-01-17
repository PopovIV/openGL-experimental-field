#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

enum class TextureClass {
	DIFFUSE,
	NORMAL,
	SPECULAR
};

class Texture
{
public:
	GLuint ID;
	GLenum type;
	TextureClass texClass;
	std::string path;

	// Texture constructor
	Texture() {}; // TMP solution
	Texture(const char* image, GLenum texType, TextureClass texClass, GLenum slot, GLenum format, GLenum pixelType);

	// Assign texture unit to texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Bind texture
	void Bind() { glBindTexture(type, ID); };
	// Unbind texture
	void Unbind() { glBindTexture(type, 0); };
	// Delete texture
	void Delete() { glDeleteTextures(1, &ID); };
};
#endif // ! TEXTURE_CLASS_H
