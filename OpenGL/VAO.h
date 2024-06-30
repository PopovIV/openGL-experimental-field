#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

// Vertex array object class
class VAO
{
public:
	// Reference id of vertex array object
	GLuint ID;
	// VAO constructor
	VAO() { glGenVertexArrays(1, &ID); };

	// Link VBO to VAO using certain layout
	void LinkVBO(VBO& VBO, GLuint layout);
	// Bind VAO
	void Bind() { glBindVertexArray(ID); };
	// Unbind VAO
	void Unbind() { glBindVertexArray(0); };
	// Delete VAO
	void Delete() { glDeleteVertexArrays(1, &ID); };
};
#endif // ! VAO_CLASS_H
