#include"Texture.h"

// Texture constructor
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Assign the type of texture object
	type = texType;

	// Store the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flip the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Read the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generate an OpenGL texture object
	glGenTextures(1, &ID);
	// Assign the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Set sampler
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configure the way the texture repeats
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assign the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generate MipMaps
	glGenerateMipmap(texType);

	// Delete the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbind the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}


// Assign texture unit to texture
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Get location of uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Set the value of uniform
	glUniform1i(texUni, unit);
}
