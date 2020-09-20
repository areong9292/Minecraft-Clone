// glad를 glfw전에 include해야한다
// glad를 위한 include 파일들은 요구되는 OpenGL 헤더들(gl.h같은)을 include한다
// 따라서 OpenGL을 필요로 하는(glfw3과 같은) 다른 헤더파일들 전에 무조건 glad를 include해야한다
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 버텍스 배열 생성
// OpenGL은 정규화 된 좌표를 처리한다
float vertices[] = {
	-0.5f, -0.5f, 0.0f,		// left
	 0.5f, -0.5f, 0.0f,		// right
	 0.0f,  0.5f, 0.0f		// top
};

// 버텍스 쉐이더 소스
const char *vertexShaderSource =
"#version 330 core\n"										// 버전 3.3
"layout (location = 0) in vec3 aPos;\n"						// 입력으로 3차원 벡터 aPos 받는다
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"		// 받은 입력으로 포지션 지정
"}\0";														// gl_Position - 버텍스 쉐이더의 출력

// 프레그먼트 쉐이더 소스
const char *fragmentShaderSource =
"#version 330 core\n"										// 버전 3.3
"out vec4 FragColor;\n"										// 출력으로 4차원 벡터 컬러 값
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"			// 컬러 값 지정
"}\0";

// 작업 후 성공 여부 체크용 변수
int  success;
char infoLog[512];

int main()
{
	// GLFW Window를 인스턴스화한다

	// GLFW init
	glfwInit();

	// glfwWindowHint - GLFW 설정을 할 때 사용하는 메소드
	// 첫번째 인자는 옵션, 두번째 인자는 해당 옵션의 값이다

	// OpenGL 버전 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	// MacOS에서는 아래 구문을 추가해야한다
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// 윈도우 생성
	GLFWwindow* window = glfwCreateWindow(800, 600,			// width, height
										"LearnOpenGL",		// 윈도우 이름 
										NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// 현재 스레드에 main context 윈도우 만들라고 한다
	glfwMakeContextCurrent(window);

	// GLAD는 함수 포인터를 관리한다
	// 그러므로 OpenGL 함수들을 호출하기 전에 GLAD를 초기화한다
	// glfwGetProcAddress - 함수 포인터 모아둔 주소
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
	}

	// 윈도우 사이즈가 변경되면 뷰포트도 그에 맞게 변경되어야한다
	// 콜백을 걸어두어 윈도우의 사이즈가 변경되었을 때 자동으로 뷰포트 지정하게 한다
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


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
		1,						// 몇 개의 쉐이더 소스 컴파일 할거냐
		&vertexShaderSource,	// 쉐이더 소스
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
		1,						// 몇 개의 쉐이더 소스 컴파일 할거냐
		&fragmentShaderSource,	// 쉐이더 소스
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
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// 쉐이더 Attach
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// 쉐이더 링크
	glLinkProgram(shaderProgram);

	// 에러체크
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

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


	/// 그래픽 카드에 데이터 저장
	// vertex buffer objects - VBO
	// 많은 수의 버텍스를 GPU 메모리에 한번에 올릴 수 있다
	// 매번 보낼 필요없이 메모리에 유지하고 있다

	// CPU -> GPU 메모리 쏘는 건 상대적으로 느리기 때문에 가능한 한번만 한다
	// = 루프 말고 한번만 보내라
	// 다른 OpenGL 객체 처럼 VBO는 유니크한 ID를 가진다
	// vertex array object - VAO
	// 인덱스 배열 객체 생성
	unsigned int VBO, VAO;

	// VAO 한 개 생성한다
	glGenVertexArrays(1, &VAO);

	// VBO 한개를 생성한다
	glGenBuffers(1, &VBO);

	// 1. 먼저 정점 배열 객체를 바인딩 한 다음
	// 2. 정점 버퍼를 바인딩하고 설정 한 다음
	// 3. 정점 속성을 구성합니다
	// 이 순서로 해야하나봄

	// glBindVertexArray - 로 바인딩 해서 VAO를 사용한다
	// 알아서 다 연결해줌
	glBindVertexArray(VAO);

	// OpenGL은 버퍼 객체들이 다양한 타입을 가지며
	// VBO는 GL_ARRAY_BUFFER 타입을 가진다
	// OpenGL은 버퍼가 서로 다른 타입이라면 한번에 여러 버퍼를 바인딩할 수 있다
	// glBindBuffer 메소드로 VBO를 GL_ARRAY_BUFFER 타겟에 바인딩한다
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// glBufferData 메소드로 이전에 정의한 버텍스 정보를
	// 버퍼 메모리에 복사할 수 있다
	glBufferData(GL_ARRAY_BUFFER,			// 우리가 데이터를 복사할 버퍼 타입
				sizeof(vertices),			// 복사 데이터 크기
				vertices,					// 복사할 데이터
				GL_STATIC_DRAW);			// 그래픽 카드가 데이터를 어떻게 다룰 것인가 정의
											// GL_STATIC_DRAW - 한번 정의, 여러 번 사용

	/// 버텍스 속성 지정
	// 각 정점의 속성은 VBO가 관리하는 메모리에서 데이터를 가져온다
	// 현재 VBO는 GL_ARRAY_BUFFER에 바인딩되어 있으므로 정점 배열의 데이터를 가져오게 된다
	glVertexAttribPointer(
						0,						// 구성하려는 정점 속성, 위치를 지정하는데 쉐이더의 location = 0 이므로 0
						3,						// 버텍스 속성의 크기 - vec3 이므로 3
						GL_FLOAT,				// 버텍스 데이터 유형 - vec3 이므로 float
						GL_FALSE,				// 데이터 정규화 여부 - 이미 정규화로 넣었으므로 false
						3 * sizeof(float),		// 정점 별 메모리 보폭 계산
						(void*)0);				// 데이터 버퍼가 시작하는 위치

	glEnableVertexAttribArray(0);


	// note that this is allowed,
	// the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object
	// so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards
	// so other VAO calls won't accidentally modify this VAO,
	// but this rarely happens.
	// Modifying other VAOs requires a call to glBindVertexArray anyways
	// so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// Render loop
	// 윈도우 종료 때까지 계속 반복하면서 렌더링한다
	while (!glfwWindowShouldClose(window))
	{
		// 입력 처리
		processInput(window);

		// 렌더링 처리
		// 클리어 색상 지정
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// GL_COLOR_BUFFER_BIT - 컬러 버퍼 클리어
		glClear(GL_COLOR_BUFFER_BIT);

		// 오브젝트 렌더링할 때 우리의 쉐이더 프로그램을 사용하겠다
		glUseProgram(shaderProgram);

		// VAO가 하나뿐이므로 매번 바인딩 할 필요는 없지만
		// 좀 더 체계적으로 유지하기 위해 매번 바인딩한다
		glBindVertexArray(VAO);

		// 오브젝트를 그린다
		glDrawArrays(GL_TRIANGLES,	// 삼각형 그린다
			0,						// 정점의 시작점
			3);						// 정점의 수

		// 더블 버퍼로 렌더링 버퍼, 준비 버퍼 둘이 바꾼다
		glfwSwapBuffers(window);

		// 이벤트나 트리거가 발생하는지 체크(키 입력, 마우스 이벤트 등등)
		// 체크 후 윈도우 상태를 업데이트하고 그 상태에 맞는 함수를 호출한다
		glfwPollEvents();
	}

	// GLFW 자원을 해제한다
	glfwTerminate();


	return 0;
}

// 윈도우 사이즈 변경 시 호출되는 콜백
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 뷰포트 지정 - 뷰포트는 glfw보다 작은 차원으로 설정할 수 있다
	// 렌더링 전, 렌더링 될 윈도우 크기(픽셀)을 지정한다
	glViewport(0, 0,			// 왼쪽 위 좌표
		width, height);			// width, height
}

// 입력 처리 메소드
void processInput(GLFWwindow* window)
{
	// esc 키 누르면 윈도우 종료 셋팅
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// 쉐이더 생성, 셋팅 및 링크
void SetShader()
{
	
}