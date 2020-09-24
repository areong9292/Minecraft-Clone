#include "ShaderManager.h"

ShaderManager::ShaderManager(const char * vertexPath, const char * fragmentPath)
{
	// 1. load shader file and read code
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	stringstream vShaderStream, fShaderStream;

	// ifstream exception 셋팅
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

	// c 스타일로 변환
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();


	// 2. compile shader
	// 작업 후 성공 여부 체크용 변수
	int  success;
	char infoLog[512];

	/// 쉐이더 셋팅
	/// 버텍스 쉐이더
	// 모던 OpenGL에서는 무언가를 렌더링 하려면
	// 최소 버텍스, 프레그먼트 쉐이더를 정의해야한다
	// 쉐이더를 사용하려면 GLSL로 쉐이더를 작성하고 컴파일 해야한다

	// 유니크한 ID를 가지는 쉐이더 객체 생성하고 해당 아이디로 제어한다
	// GL_VERTEX_SHADER - 버텍스 쉐이더 타입
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 쉐이더 소스를 등록하고 컴파일한다
	glShaderSource(vertexShader,			// 쉐이더 객체
		1,									// 몇 개의 쉐이더 소스 컴파일 할거냐
		&vShaderCode,						// 쉐이더 소스
		NULL);

	glCompileShader(vertexShader);


	// 컴파일 후 컴파일 성공, 실패 여부 체크로직
	// GL_COMPILE_STATUS - 컴파일 상태 가져온다
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// glGetShaderInfoLog - 쉐이더의 로그를 가져온다
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	/// 프레그먼트 쉐이더
	// 유니크한 ID를 가지는 쉐이더 객체 생성하고 해당 아이디로 제어한다
	// GL_FRAGMENT_SHADER - 프래그먼트 쉐이더 타입
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 쉐이더 소스를 등록하고 컴파일한다
	glShaderSource(fragmentShader,			// 쉐이더 객체
		1,									// 몇 개의 쉐이더 소스 컴파일 할거냐
		&fShaderCode,						// 쉐이더 소스
		NULL);

	glCompileShader(fragmentShader);

	// 컴파일 후 컴파일 성공, 실패 여부 체크로직
	// GL_COMPILE_STATUS - 컴파일 상태 가져온다
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// glGetShaderInfoLog - 쉐이더의 로그를 가져온다
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Shader Program 객체로 컴파일한 쉐이더들을 연결시킨다
	ID = glCreateProgram();

	// 쉐이더 Attach
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// 쉐이더 링크
	glLinkProgram(ID);

	// 에러체크
	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		// glGetProgramInfoLog - Program의 로그를 가져온다
		glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGTAM::LINK_FAILED\n" << infoLog << endl;
	}

	// 모든 쉐이더, 렌더링 콜은 glUseProgram로 호출되며
	// 더 이상 쓰지 않는다
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
