#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

	// Bind vertex array object
	VAO.Bind();

	// Create vertex buffer object and link it to vertices
	VBO VBO(vertices);
	// Create elements buffer object and link it to indices
	EBO EBO(indices);

	// Link VBO to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	// Unbind all
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Activate shader and bind VAO
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numNormal = 0;
	unsigned int numSpecular = 0;

	// Bind textures
	for (int i = 0; i < textures.size(); i++) {
		std::string num;
		std::string type;
		switch (textures[i].texClass) {
		    case(TextureClass::DIFFUSE):
				num = std::to_string(numDiffuse++);
				type = "diffuse";// TODO: remove this hardcode
				break;
			case(TextureClass::NORMAL):
				num = std::to_string(numNormal++);
				type = "normal";// TODO: remove this hardcode
				break;
			case(TextureClass::SPECULAR):
				num = std::to_string(numSpecular++);
				type = "specular";// TODO: remove this hardcode
				break;
		}

		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	// Bind constants
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
	camera.UpdateMatrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
