#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

// OpenGL ����� glad�� �ʿ�� �Ѵ�
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
};

#endif
