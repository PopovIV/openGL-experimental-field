#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

// Elements buffer object class
class EBO
{
public:
	// Reference id of elements buffer object
	GLuint ID;
	// EBO constructor
	EBO(GLuint* indices, GLsizeiptr size);

	// Bind EBO
	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); };
	// Unbind EBO
	void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };
	// Delete EBO
	void Delete() { glDeleteBuffers(1, &ID); };
};
#endif // ! EBO_CLASS_H