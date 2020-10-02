#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

// OpenGL ����� glad�� �ʿ�� �Ѵ�
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLMHeader.h"

using namespace std;

// ���̴� ������ �а� ������, ��ũ, ���� üũ�ϴ� Ŭ����
class ShaderManager
{
public:
	unsigned int ID;			// ���̴� ���α׷� ID

	// ���̴� ���� �ε�
	ShaderManager(const char* vertexPath, const char* fragmentPath);

	void Destroy();

	// ���̴� ���α׷� Ȱ��ȭ
	void use();

	// ������ ����
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;

	// ������ - glm ��ü ����
	void setVec2(const string &name, const vec2 &value) const;
	void setVec2(const string &name, float x, float y) const;

	void setVec3(const string &name, const vec3 &value) const;
	void setVec3(const string &name, float x, float y, float z) const;

	void setVec4(const string &name, const vec4 &value) const;
	void setVec4(const string &name, float x, float y, float z, float w) const;

	void setMat2(const string &name, const mat2 mat) const;
	void setMat3(const string &name, const mat3 mat) const;
	void setMat4(const string &name, const mat4 mat) const;

private:
	void checkCompileErrors(GLuint shader, string type);
};

#endif
