#include"Camera.h"

// Camera constructor
Camera::Camera(int windowWidth, int windowHeight, glm::vec3 position)
{
	Camera::windowWidth = windowWidth;
	Camera::windowHeight = windowHeight;
	Camera::position = position;
}


// Update the camera matrix
void Camera::Update(float FOVdeg, float nearPlane, float farPlane)
{
	// Init matrices
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(position, position + direction, up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)(windowWidth / windowHeight), nearPlane, farPlane);

	viewProj = projection * view;
}


// Export the camera matrix to the Vertex Shader
void Camera::UpdateMatrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(viewProj));
}

// Handle camera inputs
// TODO: really should rewrite this later
void Camera::HandleInput(GLFWwindow* window)
{
	// Handle key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += speed * direction;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position += speed * -glm::normalize(glm::cross(direction, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position += speed * -direction;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += speed * glm::normalize(glm::cross(direction, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	} else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}

	// Handle mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// Hide mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevent camera from jumping on the first click
		if (firstClick) {
			glfwSetCursorPos(window, (windowWidth / 2), (windowHeight / 2));
			firstClick = false;
		}

		// Store the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetch the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (windowHeight / 2)) / windowHeight;
		float rotY = sensitivity * (float)(mouseX - (windowWidth / 2)) / windowWidth;

		// Calculate upcoming vertical change in the direction
		glm::vec3 newDirection = glm::rotate(direction, glm::radians(-rotX), glm::normalize(glm::cross(direction, up)));

		// Decide whether or not the next vertical direction is legal or not
		if (abs(glm::angle(newDirection, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
			direction = newDirection;
		}

		// Rotate the direction left and right
		direction = glm::rotate(direction, glm::radians(-rotY), up);

		// Set mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (windowWidth / 2), (windowHeight / 2));
	} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		// Unhide cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Make sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}