#include "ShaderManager.h"

ShaderManager::ShaderManager(const char * vertexPath, const char * fragmentPath)
{
	LoadShader(vertexPath, fragmentPath);
}

ShaderManager::ShaderManager(ShaderType type)
{
	switch (type)
	{
	case ShaderManager::DEFAULT:
		LoadShader("../Shader/DefaultShader.vs", "../Shader/DefaultShader.fs");
		break;
	case ShaderManager::AMBIENT:
		LoadShader("../Shader/AmbientShader.vs", "../Shader/AmbientShader.fs");
		break;
	case ShaderManager::DIFFUSE:
		LoadShader("../Shader/DiffuseShader.vs", "../Shader/DiffuseShader.fs");
		break;
	case ShaderManager::SPECULAR:
		LoadShader("../Shader/SpecularShader.vs", "../Shader/SpecularShader.fs");
		break;
	case ShaderManager::MATERIAL:
		LoadShader("../Shader/MaterialShader.vs", "../Shader/MaterialShader.fs");
		break;
	default:
		break;
	}
}

void ShaderManager::LoadShader(const char * vertexPath, const char * fragmentPath)
{
	// 1. load shader file and read code
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	stringstream vShaderStream, fShaderStream;

	// ifstream exception ����
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		// open file
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// load file
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close file
		vShaderFile.close();
		fShaderFile.close();

		// stream to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	// c ��Ÿ�Ϸ� ��ȯ
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	CompileShader(vShaderCode, fShaderCode);
}

void ShaderManager::CompileShader(const char* vShaderCode, const char* fShaderCode)
{
	// 2. compile shader
	// �۾� �� ���� ���� üũ�� ����
	//int  success;
	//char infoLog[512];

	/// ���̴� ����
	/// ���ؽ� ���̴�
	// ��� OpenGL������ ���𰡸� ������ �Ϸ���
	// �ּ� ���ؽ�, �����׸�Ʈ ���̴��� �����ؾ��Ѵ�
	// ���̴��� ����Ϸ��� GLSL�� ���̴��� �ۼ��ϰ� ������ �ؾ��Ѵ�

	// ����ũ�� ID�� ������ ���̴� ��ü �����ϰ� �ش� ���̵�� �����Ѵ�
	// GL_VERTEX_SHADER - ���ؽ� ���̴� Ÿ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// ���̴� �ҽ��� ����ϰ� �������Ѵ�
	glShaderSource(vertexShader,			// ���̴� ��ü
		1,									// �� ���� ���̴� �ҽ� ������ �Ұų�
		&vShaderCode,						// ���̴� �ҽ�
		NULL);

	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	/// �����׸�Ʈ ���̴�
	// ����ũ�� ID�� ������ ���̴� ��ü �����ϰ� �ش� ���̵�� �����Ѵ�
	// GL_FRAGMENT_SHADER - �����׸�Ʈ ���̴� Ÿ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴� �ҽ��� ����ϰ� �������Ѵ�
	glShaderSource(fragmentShader,			// ���̴� ��ü
		1,									// �� ���� ���̴� �ҽ� ������ �Ұų�
		&fShaderCode,						// ���̴� �ҽ�
		NULL);

	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	// Shader Program ��ü�� �������� ���̴����� �����Ų��
	ID = glCreateProgram();

	// ���̴� Attach
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// ��� ���̴�, ������ ���� glUseProgram�� ȣ��Ǹ�
	// �� �̻� ���� �ʴ´�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderManager::Destroy()
{
	glDeleteProgram(ID);
}

void ShaderManager::use()
{
	// ������Ʈ �������� �� �츮�� ���̴� ���α׷��� ����ϰڴ�
	glUseProgram(ID);
}

void ShaderManager::setBool(const string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderManager::setInt(const string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderManager::setFloat(const string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderManager::setVec2(const string & name, const vec2 & value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec2(const string & name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void ShaderManager::setVec3(const string & name, const vec3 & value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec3(const string & name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void ShaderManager::setVec4(const string & name, const vec4 & value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec4(const string & name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void ShaderManager::setMat2(const string & name, const mat2 mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderManager::setMat3(const string & name, const mat3 mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderManager::setMat4(const string & name, const mat4 mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderManager::checkCompileErrors(GLuint shader, string type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		// ������ �� ������ ����, ���� ���� üũ����
		// GL_COMPILE_STATUS - ������ ���� �����´�
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			// glGetShaderInfoLog - ���̴��� �α׸� �����´�
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		// ����üũ
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			// glGetProgramInfoLog - Program�� �α׸� �����´�
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
