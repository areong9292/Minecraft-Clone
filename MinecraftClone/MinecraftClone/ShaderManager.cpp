#include "ShaderManager.h"

ShaderManager::ShaderManager(const char * vertexPath, const char * fragmentPath)
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


	// 2. compile shader
	// �۾� �� ���� ���� üũ�� ����
	int  success;
	char infoLog[512];

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


	// ������ �� ������ ����, ���� ���� üũ����
	// GL_COMPILE_STATUS - ������ ���� �����´�
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// glGetShaderInfoLog - ���̴��� �α׸� �����´�
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

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

	// ������ �� ������ ����, ���� ���� üũ����
	// GL_COMPILE_STATUS - ������ ���� �����´�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// glGetShaderInfoLog - ���̴��� �α׸� �����´�
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Shader Program ��ü�� �������� ���̴����� �����Ų��
	ID = glCreateProgram();

	// ���̴� Attach
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(ID);

	// ����üũ
	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		// glGetProgramInfoLog - Program�� �α׸� �����´�
		glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGTAM::LINK_FAILED\n" << infoLog << endl;
	}

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
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
