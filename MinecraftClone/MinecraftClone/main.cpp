// glad를 glfw전에 include해야한다
// glad를 위한 include 파일들은 요구되는 OpenGL 헤더들(gl.h같은)을 include한다
// 따라서 OpenGL을 필요로 하는(glfw3과 같은) 다른 헤더파일들 전에 무조건 glad를 include해야한다
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

		// 이벤트나 트리거가 발생하는지 체크(키 입력, 마우스 이벤트 등등)
		// 체크 후 윈도우 상태를 업데이트하고 그 상태에 맞는 함수를 호출한다
		glfwPollEvents();

		// 더블 버퍼로 렌더링 버퍼, 준비 버퍼 둘이 바꾼다
		glfwSwapBuffers(window);
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