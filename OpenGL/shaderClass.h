#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Utility function to get file  content in string format
std::string get_file_contents(const char* filename);

// Shader class
class Shader
{
public:
	// Reference ID of shader program object
	GLuint ID;
	// Shader class constructor from two different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activate shader program
	void Activate() { glUseProgram(ID); };
	// Delete shader program
	void Delete() { glDeleteProgram(ID); };
private:
	// Shader compilation checker
	void CompileErrors(unsigned int shader, const char* type);
};
#endif // ! SHADER_CLASS_H
