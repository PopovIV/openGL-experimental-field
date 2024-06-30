#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "EBO.h"
#include "VAO.h"


#define WINDOW_HEIGHT 800
#define WINDOW_WIDHT 800

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
};


// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Upper triangle
	5, 4, 1  // Lower right triangle
};


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

	// Create shader program using default shaders
	Shader shaderProgram("default.vert", "default.frag");

	// Create vertex array object and bind it
	VAO VAO1;
	VAO1.Bind();

	// Create vertex buffer object and link it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Create elements buffer object and link it to indices
	EBO EBO1(indices, sizeof(indices));

	// Link VBO to VAO
	VAO1.LinkVBO(VBO1, 0);

	// Unbind all
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Set up shader program
		shaderProgram.Activate();
		// Bind VAO
		VAO1.Bind();
		
		// Draw call
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);

		// Event handling
		glfwPollEvents();
	}

	// Delete buffers
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroy window
	glfwDestroyWindow(window);
	// Teriminate GLFW
	glfwTerminate();

	return 0;
}
