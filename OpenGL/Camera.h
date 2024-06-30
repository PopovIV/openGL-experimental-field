#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

// Camera class
class Camera
{
public:
	// Camera constructor
	Camera(int windowWidth, int windowHeight, glm::vec3 position);

	// Update and export the camera matrix to the Vertex Shader
	void Update(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handle camera inputs
	void HandleInput(GLFWwindow* window);
private:
	// Main camera data
	glm::vec3 position;
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevent the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Store the width and height of the window
	int windowWidth;
	int windowHeight;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;
};
#endif // ! CAMERA_CLASS_H
