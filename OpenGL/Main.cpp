#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	// Set back buffer color
	glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
	// Clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	// Destroy window
	glfwDestroyWindow(window);
	// Teriminate GLFW
	glfwTerminate();

	return 0;
}
