#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <vector>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

// Represents container for game object data needed for rendering and updating
class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	// Draw function
	void Draw(Shader& shader, Camera& camera);
private:
	VAO VAO;

	// data for rendering
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
};
#endif // ! MESH_CLASS_H
