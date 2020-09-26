// glad를 glfw전에 include해야한다
// glad를 위한 include 파일들은 요구되는 OpenGL 헤더들(gl.h같은)을 include한다
// 따라서 OpenGL을 필요로 하는(glfw3과 같은) 다른 헤더파일들 전에 무조건 glad를 include해야한다
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderManager.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 버텍스, 인덱스 생성
// OpenGL은 정규화 된 좌표를 처리한다
float vertices[] = {
	// position					// colors
	 0.0f,  0.5f, 0.0f,			0.0f, 0.0f, 1.0f,	// top
	 0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f,	// bottom right
	-0.5f, -0.5f, 0.0f,			1.0f, 0.0f, 0.0f,	// bottom left
};

// note that we start from 0!
unsigned int indices[] = {
	0, 1, 2,   // first triangle
};

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

	ShaderManager ourShader("../Shader/shader.vs", "../Shader/shader.fs");

	/// 그래픽 카드에 데이터 저장
	// vertex buffer objects - VBO
	// 많은 수의 버텍스를 GPU 메모리에 한번에 올릴 수 있다
	// 매번 보낼 필요없이 메모리에 유지하고 있다
	// CPU -> GPU 메모리 쏘는 건 상대적으로 느리기 때문에 가능한 한번만 한다
	// = 루프 말고 한번만 보내라
	// 다른 OpenGL 객체 처럼 유니크한 ID를 가진다

	// VBO에 접근하는 배열
	// vertex array object - VAO

	// 인덱스 배열
	// element buffer objects - EBO

	unsigned int VBO, VAO, EBO;

	// VAO 한개를 생성한다
	glGenVertexArrays(1, &VAO);

	// VBO 한개를 생성한다
	glGenBuffers(1, &VBO);

	// EBO 한개를 생성한다
	glGenBuffers(1, &EBO);

	// 1. 먼저 정점 배열 객체를 바인딩 한 다음
	// 2. 정점 버퍼를 바인딩하고 설정 한 다음
	// 3. 정점 속성을 구성합니다
	// 이 순서로 해야하나봄

	// glBindVertexArray - 로 바인딩 해서 VAO를 사용한다
	// 그러면 VBO에 알아서 다 연결해 정점 배열 사용해서 동작한다
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

	// EBO를 GL_ELEMENT_ARRAY_BUFFER로 등록
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// GL_ELEMENT_ARRAY_BUFFER에 인덱스 배열을 등록한다
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,	// 우리가 데이터를 복사할 버퍼 타입
				sizeof(indices),			// 복사 데이터 크기
				indices,					// 복사할 데이터
				GL_STATIC_DRAW);			// 그래픽 카드가 데이터를 어떻게 다룰 것인가 정의
											// GL_STATIC_DRAW - 한번 정의, 여러 번 사용

	/// 버텍스 속성 지정
	// 각 정점의 속성은 VBO가 관리하는 메모리에서 데이터를 가져온다
	// 현재 VBO는 GL_ARRAY_BUFFER에 바인딩되어 있으므로 정점 배열의 데이터를 가져오게 된다
	// position attribute
	glVertexAttribPointer(
						0,								// 구성하려는 정점 속성, 위치를 지정하는데 쉐이더의 location = 0 이므로 0
						3,								// 버텍스 속성의 크기 - vec3 이므로 3
						GL_FLOAT,						// 버텍스 데이터 유형 - vec3 이므로 float
						GL_FALSE,						// 데이터 정규화 여부 - 이미 정규화로 넣었으므로 false
						6 * sizeof(float),				// 정점 별 메모리 보폭 계산
						(void*)0);						// 데이터 버퍼가 시작하는 위치

	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(
						1,								// 구성하려는 정점 속성, 컬러를 지정하는데 쉐이더의 location = 1 이므로 1
						3,								// 버텍스 속성의 크기 - vec3 이므로 3
						GL_FLOAT,						// 버텍스 데이터 유형 - vec3 이므로 float
						GL_FALSE,						// 데이터 정규화 여부 - 이미 정규화로 넣었으므로 false
						6 * sizeof(float),				// 정점 별 메모리 보폭 계산
						(void*)(3 * sizeof(float)));	// 데이터 버퍼가 시작하는 위치 - 포지션 3개 뒤에 컬러이므로 3 * float로 포지션 위치 건너뛴다

	glEnableVertexAttribArray(1);


	// note that this is allowed,
	// glVertexAttribPointer 호출은 VBO를
	// the vertex attribute's bound vertex buffer object 로 등록한다
	// 이후 안전하게 바인딩을 해제할 수 있다
	// -> 이미 등록되었기 때문에 해제 가능하다...?
	// 찾아보니 안정성을 위해 null 버퍼 바인딩 하는 듯?

	// We’re done uploading, so unbind the buffer for safety.
	// 안전을 위해 이미 업로드 된 버퍼를 언바인딩한다
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember:
	// do NOT unbind the EBO while a VAO is active
	// as the bound element buffer object is stored in the VAO;
	// keep the EBO bound.
	// 바인딩 된 EBO가 VAO에 저장되므로
	// VAO가 활성화되어있는 동안 EBO를 해제하지 마십시오.
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards
	// VAO 또한 바인딩 해제할 수 있다
	// so other VAO calls won't accidentally modify this VAO, but this rarely happens.
	// 그래서 다른 VAO 호출들은 실수로 이 VAO를 수정하지 않지만, 가끔 일어날 수 있다
	// Modifying other VAOs requires a call to glBindVertexArray anyways
	// 다른 VAO를 수정하는 것도 glBindVertexArray가 호출되야한다
	// so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// 그래서 일반적으로는 VAO (또는 VBO)가 직접적으로 필요하지 않은 경우
	// 바인딩을 해제하지 않습니다.

	// 위 번역을 정리하면 VAO가 바인딩 되어있으면
	// 물론 다른 VAO가 이 VAO를 건들지는 않겠지만 혹시나 하는 실수로
	// 우리가 그리고자 하는 VBO와 연동된 VAO가 망가질 수 있다
	// 실수를 피하기 위해 바인딩을 해제한다
	glBindVertexArray(0);

	// wireframe polygons 로 그릴꺼면 주석 해제
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//float timeValue;
	//float greenValue;

	// 쉐이더에서 outColor 유니폼을 가져온다
	//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

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

		ourShader.use();
		ourShader.setFloat("ourColor", 1.0f);
		/*
		// 오브젝트 렌더링할 때 우리의 쉐이더 프로그램을 사용하겠다
		glUseProgram(shaderProgram);

		// 계속 시간 값을 가져와 색상을 변경한다
		timeValue = glfwGetTime();
		greenValue = (sin(timeValue) / 2.0f) + 0.5f;

		// 가져온 유니폼에 값을 셋팅한다
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		*/
		// VAO가 하나뿐이므로 매번 바인딩 할 필요는 없지만
		// 좀 더 체계적으로 유지하기 위해 매번 바인딩한다
		// 위에서 0으로 바인딩 해제한 것과 같은 맥락
		glBindVertexArray(VAO);

		// 오브젝트를 그린다
		// 인덱스 사용이므로 glDrawArrays -> glDrawElements 변경
		// glDrawElements가 사용하는 인덱스는 EBO로 등록한 인덱스 배열이다
		glDrawElements(GL_TRIANGLES,	// 삼각형 그린다
			6,							// 정점의 수
			GL_UNSIGNED_INT,			// 인덱스 배열의 타입
			0);							// 인덱스 배열 시작점

		// 더블 버퍼로 렌더링 버퍼, 준비 버퍼 둘이 바꾼다
		glfwSwapBuffers(window);

		// 이벤트나 트리거가 발생하는지 체크(키 입력, 마우스 이벤트 등등)
		// 체크 후 윈도우 상태를 업데이트하고 그 상태에 맞는 함수를 호출한다
		glfwPollEvents();
	}

	// 사용한 GL 객체들 해제
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	ourShader.Destroy();

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
