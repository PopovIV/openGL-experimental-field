#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"


#define WINDOW_HEIGHT 800
#define WINDOW_WIDHT 1200
#define FIELD_OF_VIEW 45.0f
#define Z_NEAR 0.1f
#define Z_FAR 100.0f

// Vertices coordinates
Vertex pyramidVertices[] =
{ //                 COORDINATES     /        NORMALS                     /          COLORS        /        TEXTURE COORDS      //
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)}, // Bottom side
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 5.0f)}, // Bottom side
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(5.0f, 5.0f)}, // Bottom side
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(5.0f, 0.0f)}, // Bottom side

	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)}, // Left Side
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(5.0f, 0.0f)}, // Left Side
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(2.5f, 5.0f)}, // Left Side

	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(5.0f, 0.0f)}, // Non-facing side
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)}, // Non-facing side
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(2.5f, 5.0f)}, // Non-facing side

	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)}, // Right side
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(5.0f, 0.0f)}, // Right side
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(2.5f, 5.0f)}, // Right side

	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(5.0f, 0.0f)}, // Facing side
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)}, // Facing side
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(2.5f, 5.0f)} // Facing side
};


// Indices for vertices order
GLuint pyramidIndices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};


// Vertices coordinates
Vertex floorVertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-100.0f, 0.0f,  100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-100.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 100.0f)},
	Vertex{glm::vec3(100.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(100.0f, 100.0f)},
	Vertex{glm::vec3(100.0f, 0.0f,  100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(100.0f, 0.0f)}
};


// Indices for vertices order
GLuint floorIndices[] =
{
	0, 1, 2,
	0, 2, 3
};


Vertex cubeVertices[] =
{   //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};


// Indices for vertices order
GLuint cubeIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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

	// Textures
	Texture texturesPyramid[]
	{
        Texture("brick.png", GL_TEXTURE_2D, TextureClass::DIFFUSE, 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

    // MAIN SHADER
	// Create shader program using default shaders
	Shader shaderProgram("default.vert", "default.frag");
	// Fill mesh data
	std::vector<Vertex> verts(pyramidVertices, pyramidVertices + sizeof(pyramidVertices) / sizeof(Vertex));
	std::vector<GLuint> ind(pyramidIndices, pyramidIndices + sizeof(pyramidIndices) / sizeof(GLuint));
	std::vector<Texture> tex(texturesPyramid, texturesPyramid + sizeof(texturesPyramid) / sizeof(Texture));
	// Create pyramid mesh
	//Mesh pyramid(verts, ind, tex);


	// TODO: go to common texture array
	Texture texturesFloor[]
	{
		Texture("pool.png", GL_TEXTURE_2D, TextureClass::DIFFUSE, 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	// Fill mesh data
	std::vector<Vertex> floorVerts(floorVertices, floorVertices + sizeof(floorVertices) / sizeof(Vertex));
	std::vector<GLuint> floorInd(floorIndices, floorIndices + sizeof(floorIndices) / sizeof(GLuint));
	std::vector<Texture> floorTex(texturesFloor, texturesFloor + sizeof(texturesFloor) / sizeof(Texture));
	// Create pyramid mesh
	Mesh floor(floorVerts, floorInd, floorTex);


	// CUBE/LIGHT SHADER
	// Create shader program using light shaders
	Shader lightShader("light.vert", "light.frag");
	// Fill mesh data
	std::vector<Vertex> lightVert(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	// Create light mesh
	Mesh light(lightVert, lightInd, tex);

	// Cube and pyramid params
	float lightPos[3] = { 0.3f, 1.0f, 0.3f };
	float lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// Pyramid rotation
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Model treeModel("scene.gltf");

	// Just for this scene shit, need instancing ASAP
	const int treeCount = 100;
	glm::mat4 treeModelMatrix[treeCount];
	for (int i = 0; i < treeCount; i++) {
		treeModelMatrix[i] = glm::mat4(1.0f);
		if (i != 0) {
			treeModelMatrix[i] = glm::translate(treeModelMatrix[i], glm::vec3(-100 + (std::rand() % 200), 0, -100 + (std::rand() % 200)));
		}
		treeModelMatrix[i] = glm::rotate(treeModelMatrix[i], glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		treeModelMatrix[i] = glm::scale(treeModelMatrix[i], glm::vec3(0.5, 0.5, 0.5));
	}

	Camera camera(WINDOW_WIDHT, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	// ImGui Initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)(io);
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// dbgVar to draw 
	bool drawBox = false;

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Set up color of back buffer
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Clean back and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Camera update
		if (!io.WantCaptureMouse) {
	        camera.HandleInput(window);
		}
		camera.Update(FIELD_OF_VIEW, Z_NEAR, Z_FAR);

		// objects update
		double curTime = glfwGetTime();
		if (curTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = curTime;
		}

		// Pyramid matrix stuff
		glm::mat4 pyramidModel = glm::mat4(1.0f);

		glm::vec3 lightPosGLM = glm::vec3(lightPos[0], lightPos[1], lightPos[2]);
		lightPosGLM = glm::rotate(lightPosGLM, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		// Render floor and pyramid
		// Update shader data
		shaderProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPosGLM.x, lightPosGLM.y, lightPosGLM.z);
		floor.Draw(shaderProgram, camera);

		//pyramidModel = glm::rotate(pyramidModel, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
		//pyramid.Draw(shaderProgram, camera);

		for (int i = 0; i < treeCount; i++) {
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(treeModelMatrix[i]));

			treeModel.Draw(shaderProgram, camera);
		}

		// Render Light
		if (drawBox) {
			// Update matrices
			glm::mat4 lightModel = glm::mat4(1.0f);
			lightModel = glm::translate(lightModel, glm::vec3(lightPos[0], lightPos[1], lightPos[2]));

			// Set up light shader
			lightShader.Activate();
			// Update shader data
			glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
			glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);

			light.Draw(lightShader, camera);
		}

		// ImGui Window
		ImGui::Begin("ImGui");
		ImGui::Checkbox("Visualize light source", &drawBox);
		ImGui::SliderFloat3("Light pos", lightPos, -10.0f, 10.0f);
		ImGui::ColorEdit3("Light color", lightColor);
		//ImGui::ShowDemoWindow();
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap buffers
		glfwSwapBuffers(window);

		// Event handling
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete buffers
	shaderProgram.Delete();
	lightShader.Delete();
	for (Texture& tex : texturesPyramid) {
		tex.Delete();
	}
	for (Texture& tex : texturesFloor) {
		tex.Delete();
	}

	// Destroy window
	glfwDestroyWindow(window);
	// Teriminate GLFW
	glfwTerminate();

	return 0;
}
