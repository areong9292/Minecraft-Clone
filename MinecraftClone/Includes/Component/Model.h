#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Component.h"
#include "Mesh.h"

class Model : public Component
{
public:
	Model();
	Model(char *path, int vertexOffset, ShaderManager* shader);
	~Model();

	// 매 프레임마다 호출
	virtual void UpdateComponent() override;

	// model data
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh>    meshes;
	string directory;
	bool gammaCorrection;

private:
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

	int _verticesOffset;

	ShaderManager* _shader;
};

