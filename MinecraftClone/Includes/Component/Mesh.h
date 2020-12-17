#pragma once
// glad를 glfw전에 include해야한다
// glad를 위한 include 파일들은 요구되는 OpenGL 헤더들(gl.h같은)을 include한다
// 따라서 OpenGL을 필요로 하는(glfw3과 같은) 다른 헤더파일들 전에 무조건 glad를 include해야한다
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

	// 매 프레임마다 호출
	virtual void UpdateComponent() override;

	vector<Vertex> _vertices;		// 버텍스 배열
	vector<unsigned int> _indices;	// 인덱스 배열
	vector<Texture> _textures;		// 텍스쳐 배열

	int _verticesOffset;

	ShaderManager* _shader;

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

