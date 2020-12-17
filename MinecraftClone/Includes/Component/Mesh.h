#pragma once
// glad�� glfw���� include�ؾ��Ѵ�
// glad�� ���� include ���ϵ��� �䱸�Ǵ� OpenGL �����(gl.h����)�� include�Ѵ�
// ���� OpenGL�� �ʿ�� �ϴ�(glfw3�� ����) �ٸ� ������ϵ� ���� ������ glad�� include�ؾ��Ѵ�
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GLMHeader.h>
#include <vector>
#include "Component.h"

#include "../../MinecraftClone/ShaderManager.h"

struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;

	vec3 Tangent;
	vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh : public Component
{
public:
	Mesh();
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, int verticesOffset, ShaderManager* shader);
	~Mesh();

	// �� �����Ӹ��� ȣ��
	virtual void UpdateComponent() override;

	vector<Vertex> _vertices;		// ���ؽ� �迭
	vector<unsigned int> _indices;	// �ε��� �迭
	vector<Texture> _textures;		// �ؽ��� �迭

	int _verticesOffset;

	ShaderManager* _shader;

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

