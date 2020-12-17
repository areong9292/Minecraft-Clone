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

	// �� �����Ӹ��� ȣ��
	virtual void UpdateComponent() override;

	// model data
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh>    meshes;
	string directory;
	bool gammaCorrection;



	string ReplaceAll(string &str, const string& from, const string& to) {
		size_t start_pos = 0; //stringó������ �˻�
		while ((start_pos = str.find(from, start_pos)) != string::npos)  //from�� ã�� �� ���� ������
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // �ߺ��˻縦 ���ϰ� from.length() > to.length()�� ��츦 ���ؼ�
		}
		return str;
	}

private:
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

	int _verticesOffset;

	ShaderManager* _shader;
};

