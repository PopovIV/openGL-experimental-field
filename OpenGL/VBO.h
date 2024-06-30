#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

// Vertex buffer object class
class VBO
{
public:
	// Reference id of vertex buffer object
	GLuint ID;
	// VBO constructor
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Bind VBO
	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); };
	// Unbind VBO
	void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
	// Delete VBO
	void Delete() { glDeleteBuffers(1, &ID); };
};
#endif // ! VBO_CLASS_H
