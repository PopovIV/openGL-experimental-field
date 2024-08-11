#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

// Containder for meshes 
class Model
{
public:
    Model(std::string path);
    void Draw(Shader& shader, Camera& camera);
private:
    // model data
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::string directory;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureClass textureClass);
};
#endif // ! MODEL_CLASS_H
