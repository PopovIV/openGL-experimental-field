#include "shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);

	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}

	throw(errno);
}


// Shader class constructor
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertex and fragment files
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert shader source strings to character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach vertex shader source to vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile vertex shader into machine code
	glCompileShader(vertexShader);
	CompileErrors(vertexShader, "VERTEX");

	// Create fragment shader and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach fragment shader source to fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile fragment shader into machine code
	glCompileShader(fragmentShader);
	CompileErrors(vertexShader, "FRAGMENT");

	// Create a shader program and get its reference
	ID = glCreateProgram();
	// Attach vertex shader and fragment shader to shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Link all shaders into shader program
	glLinkProgram(ID);

	// Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


// Shader compilation checker
void Shader::CompileErrors(unsigned int shader, const char* type)
{
	// Compilation flag
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}
