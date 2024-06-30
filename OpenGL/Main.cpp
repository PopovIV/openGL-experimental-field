#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture.h"
#include "shaderClass.h"
#include "EBO.h"
#include "VAO.h"


#define WINDOW_HEIGHT 800
#define WINDOW_WIDHT 800

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};


int main() {
	// Initialize GLFW
	glfwInit();

	// Give a GLFW a hint about version of OpenGL
	// In this project it is currently OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW that we are using CORE profile
	// So we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	// For basics 6 floats is per vertex data rn
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// ID of uniform variable called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Texture
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Set up shader program
		shaderProgram.Activate();

		// Set up uniform variable
		glUniform1f(uniID, 0.5f);

		// Bind texture
		popCat.Bind();

		// Bind VAO
		VAO1.Bind();
		
		// Draw call
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	popCat.Delete();

	// Destroy window
	glfwDestroyWindow(window);
	// Teriminate GLFW
	glfwTerminate();

	return 0;
}
