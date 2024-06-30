#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


#define WINDOW_HEIGHT 800
#define WINDOW_WIDHT 800

int main() {
	// Initialize GLFW
	glfwInit();

	// Give a GLFW a hint about version of OpenGL
	// In this project it is currently OpenGL 3.3
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW that we are using CORE profile
	// So we only have the modern functions
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices array for triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // llc
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lrc
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // ucc
	};

	// Create window class
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDHT, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	
	// Error handling
	if (!window) {
		std::cout << "Failed to create GLTF window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Connect the window to current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures openGL
	gladLoadGL();

	// Set up the viewport
	glViewport(0, 0, WINDOW_WIDHT, WINDOW_HEIGHT);

	// Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach vertex shader source to vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile vertex shader into machine code
	glCompileShader(vertexShader);

	// Create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach fragment shader source to fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile fragment shader into machine code
	glCompileShader(fragmentShader);

	// Create a shader program
	GLuint shaderProgram = glCreateProgram();
	// Attach vertex shader and fragment shader to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link all shaders into shader program
	glLinkProgram(shaderProgram);

	// Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create vertex array object(VAO)
	// !! Create always before VBO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Create vertex buffer object(VBO)
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// Bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Store vertices in VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure vertex  attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Set back buffer color
	glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
	// Clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Set up shader program
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		
		// Draw call
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers
		glfwSwapBuffers(window);

		// Event handling
		glfwPollEvents();
	}

	// Delete buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Destroy window
	glfwDestroyWindow(window);
	// Teriminate GLFW
	glfwTerminate();

	return 0;
}
