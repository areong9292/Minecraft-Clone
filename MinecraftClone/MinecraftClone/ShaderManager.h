#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

// OpenGL 헤더는 glad를 필요로 한다
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLMHeader.h"

using namespace std;

// 쉐이더 파일을 읽고 컴파일, 링크, 오류 체크하는 클래스
class ShaderManager
{
public:
	unsigned int ID;			// 쉐이더 프로그램 ID

	// 쉐이더 파일 로드
	ShaderManager(const char* vertexPath, const char* fragmentPath);

	void Destroy();

	// 쉐이더 프로그램 활성화
	void use();

	// 유니폼 셋팅
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;

	// 유니폼 - glm 객체 셋팅
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
