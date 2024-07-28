#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

// Tmp vertex class
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

// Vertex buffer object class
class VBO
{
public:
	// Reference id of vertex buffer object
	GLuint ID;
	// VBO constructor
	VBO(std::vector<Vertex>& vertices);

	// Bind VBO
	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); };
	// Unbind VBO
	void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
	// Delete VBO
	void Delete() { glDeleteBuffers(1, &ID); };
};
#endif // ! VBO_CLASS_H
