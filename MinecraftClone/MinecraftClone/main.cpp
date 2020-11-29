// glad를 glfw전에 include해야한다
// glad를 위한 include 파일들은 요구되는 OpenGL 헤더들(gl.h같은)을 include한다
// 따라서 OpenGL을 필요로 하는(glfw3과 같은) 다른 헤더파일들 전에 무조건 glad를 include해야한다
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderManager.h"

#include <GLMHeader.h>

#include "Camera.h"

#include <string>

// Image Loader Library
// 관련 정의 소스 코드 만 포함하도록 헤더 파일을 수정하여
// 효과적으로 헤더 파일을 .cpp 파일로 변환합니다.
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// 버텍스, 인덱스 생성
// OpenGL은 정규화 된 좌표를 처리한다
/*float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
};*/

int verticesOffset = 11;
float vertices[] = {
	-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,	0.0f,  1.0f,  0.0f
};

// 큐브들 위치
vec3 cubePositions[] = {
	vec3(0.0f, 0.0f, 0.0f),
	vec3(2.0f,  5.0f, -15.0f),
	vec3(-1.5f, -2.2f, -2.5f),
	vec3(-3.8f, -2.0f, -12.3f),
	vec3(2.4f, -0.4f, -3.5f),
	vec3(-1.7f,  3.0f, -7.5f),
	vec3(1.3f, -2.0f, -2.5f),
	vec3(1.5f,  2.0f, -2.5f),
	vec3(1.5f,  0.2f, -1.5f),
	vec3(-1.3f,  1.0f, -1.5f)
};

// 라이트 위치
vec3 pointLightPositions[] = {
	vec3(0.7f,  0.2f,  2.0f),
	vec3(2.3f, -3.3f, -4.0f),
	vec3(-4.0f,  2.0f, -12.0f),
	vec3(0.0f,  0.0f, -3.0f)
};

// 작업 후 성공 여부 체크용 변수
int  success;
char infoLog[512];

// stores how much we're seeing of either texture
float mixValue = 0.2f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/// 카메라 관련 변수
Camera* sceneCamera = nullptr;
/*
// 카메라 위치
vec3 cameraPos;

// 카메라 타겟
vec3 cameraTarget;

// 카메라 방향 벡터
vec3 cameraFront;

// 카메라 업 벡터
vec3 cameraUp;

// 카메라 이동 속도
float cameraSpeed = 0.05f;

/// 프레임 계산
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
double lastX = 0;
double lastY = 0;
float m_yaw = -90.0f;
float m_pitch = 0.0f;
float Zoom = 45.0f;
*/
/// 프레임 계산
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	/// glm 테스트
	// 벡터, 행렬 선언
	vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	mat4 trans = glm::mat4(1.0f);

	// 1,1,0 이동행렬 만듬
	trans = translate(trans, vec3(1.0f, 1.0f, 0.0f));

	// 벡터 이동
	vec = trans * vec;

	// 최종 이동 결과
	//cout << vec.x << vec.y << vec.z << endl;

	// 단위 행렬 셋팅
	trans = mat4(1.0f);

	// z축(vec3(0.0, 0.0, 1.0)) 기준으로 90도(radians(90.0f)) 회전하는 회전행렬만든다
	trans = rotate(trans, radians(90.0f), vec3(0.0, 0.0, 1.0));

	// xyz축 0.5배 변환행렬
	trans = scale(trans, vec3(0.5, 0.5, 0.5));


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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,			// width, height
										"LearnOpenGL",						// 윈도우 이름 
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
		glfwTerminate();
		return -1;
	}

	// 깊이 계산을 한다
	glEnable(GL_DEPTH_TEST);

	// 윈도우 사이즈가 변경되면 뷰포트도 그에 맞게 변경되어야한다
	// 콜백을 걸어두어 윈도우의 사이즈가 변경되었을 때 자동으로 뷰포트 지정하게 한다
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	ShaderManager ourShader(ShaderManager::ShaderType::MULTIPLELIGHTS);
	ShaderManager lightShader(ShaderManager::ShaderType::DEFAULT);

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

	unsigned int VBO, VAO;// , EBO;

	// VAO 한개를 생성한다
	glGenVertexArrays(1, &VAO);

	// VBO 한개를 생성한다
	glGenBuffers(1, &VBO);

	// EBO 한개를 생성한다
	//glGenBuffers(1, &EBO);

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
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// GL_ELEMENT_ARRAY_BUFFER에 인덱스 배열을 등록한다
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,	// 우리가 데이터를 복사할 버퍼 타입
	//	sizeof(indices),			// 복사 데이터 크기
	//	indices,					// 복사할 데이터
	//	GL_STATIC_DRAW);			// 그래픽 카드가 데이터를 어떻게 다룰 것인가 정의
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
		verticesOffset * sizeof(float),	// 정점 별 메모리 보폭 계산
		(void*)0);						// 데이터 버퍼가 시작하는 위치

	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(
		1,								// 구성하려는 정점 속성, 컬러를 지정하는데 쉐이더의 location = 1 이므로 1
		3,								// 버텍스 속성의 크기 - vec3 이므로 3
		GL_FLOAT,						// 버텍스 데이터 유형 - vec3 이므로 float
		GL_FALSE,						// 데이터 정규화 여부 - 이미 정규화로 넣었으므로 false
		verticesOffset * sizeof(float),	// 정점 별 메모리 보폭 계산
		(void*)(3 * sizeof(float)));	// 데이터 버퍼가 시작하는 위치 - 포지션 3개 뒤에 컬러이므로 3 * float로 포지션 위치 건너뛴다

	glEnableVertexAttribArray(1);

	// texture attribute
	glVertexAttribPointer(
		2,								// 구성하려는 정점 속성, 컬러를 지정하는데 쉐이더의 location = 2 이므로 2
		2,								// 버텍스 속성의 크기 - vec2 이므로 2
		GL_FLOAT,						// 버텍스 데이터 유형 - vec3 이므로 float
		GL_FALSE,						// 데이터 정규화 여부 - 이미 정규화로 넣었으므로 false
		verticesOffset * sizeof(float),	// 정점 별 메모리 보폭 계산
		(void*)(6 * sizeof(float)));	// 데이터 버퍼가 시작하는 위치 - 포지션 6개 뒤에 텍스쳐이므로 6 * float로 포지션 위치 건너뛴다

	glEnableVertexAttribArray(2);

	// normal attribute
	glVertexAttribPointer(
		3,								// 구성하려는 정점 속성, 노말을 지정하는데 쉐이더의 location = 3 이므로 3
		3,								// 버텍스 속성의 크기 - vec3 이므로 3
		GL_FLOAT,						// 버텍스 데이터 유형 - vec3 이므로 float
		GL_FALSE,						// 데이터 정규화 여부 - 이미 정규화로 넣었으므로 false
		verticesOffset * sizeof(float),	// 정점 별 메모리 보폭 계산
		(void*)(8 * sizeof(float)));	// 데이터 버퍼가 시작하는 위치 - 포지션 8개 뒤에 텍스쳐이므로 8 * float로 포지션 위치 건너뛴다

	glEnableVertexAttribArray(3);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

	/// 텍스쳐 로드 및 셋팅
	// 텍스쳐 객체 생성
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);

	// 생성한 객체를 GL_TEXTURE_2D에 바인드한다
	glBindTexture(GL_TEXTURE_2D, texture1);

	// S - 오른쪽, T - 위쪽 방향
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// 만일 텍스쳐 셋팅이 GL_TEXTURE_BORDER_COLOR 인 경우
	// 바깥 색상도 지정해야한다
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// GL_NEAREST - 가장 가까운 색으로 셋팅
	// GL_LINEAR - 근처 비슷한 색상으로 셋팅
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 텍스쳐 데이터 로드
	int width, height, nrChannels;

	// 상하반전
	stbi_set_flip_vertically_on_load(true);

	// 텍스쳐 데이터 불러오기
	unsigned char* data = stbi_load(
		"../Texture/container2.png",		// 텍스쳐 파일 경로
		&width,								// 텍스쳐 width
		&height,							// 텍스쳐 height
		&nrChannels,						// 텍스쳐의 컬러 채널의 수
		0);

	if (data)
	{
		// 이전에 로드한 텍스쳐 정보로 텍스쳐를 생성시킨다
		glTexImage2D(GL_TEXTURE_2D,				// 텍스쳐 타겟 - 위에서 바인드한 텍스쳐 객체
						0,						// mipmap level - 0은 기본 셋팅
						GL_RGBA,				// 텍스쳐를 어떤 포맷으로 저장할 것인가
						width,					// 텍스쳐 width
						height,					// 텍스쳐 height
						0,						// 이건 항상 0
						GL_RGBA,				// 이미지의 포맷
						GL_UNSIGNED_BYTE,		// 데이터 유형
						data);					// 실제 이미지 데이터

		// glTexImage2D 호출 후에는
		// 바인딩 된 텍스쳐 오브젝트는 텍스쳐를 가지고 있다
		// 기본 텍스쳐만 가지고 있으며 밉맵 셋팅을 위해 glGenerateMipmap을 호출한다
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}

	// 로드한 다음 데이터 해제
	stbi_image_free(data);

	// 2번째 텍스쳐 객체 생성
	glGenTextures(1, &texture2);

	// 생성한 객체를 GL_TEXTURE_2D에 바인드한다
	glBindTexture(GL_TEXTURE_2D, texture2);

	// S - 오른쪽, T - 위쪽 방향
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 만일 텍스쳐 셋팅이 GL_TEXTURE_BORDER_COLOR 인 경우
	// 바깥 색상도 지정해야한다
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// GL_NEAREST - 가장 가까운 색으로 셋팅
	// GL_LINEAR - 근처 비슷한 색상으로 셋팅
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 텍스쳐 데이터 로드
	data = stbi_load(
		"../Texture/container2_specular.png",		// 텍스쳐 파일 경로
		&width,										// 텍스쳐 width
		&height,									// 텍스쳐 height
		&nrChannels,								// 텍스쳐의 컬러 채널의 수
		0);

	if (data)
	{
		// 이전에 로드한 텍스쳐 정보로 텍스쳐를 생성시킨다
		glTexImage2D(GL_TEXTURE_2D,	// 텍스쳐 타겟 - 위에서 바인드한 텍스쳐 객체
			0,						// mipmap level - 0은 기본 셋팅
			GL_RGBA,				// 텍스쳐를 어떤 포맷으로 저장할 것인가 - A 알파 추가
			width,					// 텍스쳐 width
			height,					// 텍스쳐 height
			0,						// 이건 항상 0
			GL_RGBA,				// 이미지의 포맷 - A 알파 추가
			GL_UNSIGNED_BYTE,		// 데이터 유형
			data);					// 실제 이미지 데이터

		// glTexImage2D 호출 후에는
		// 바인딩 된 텍스쳐 오브젝트는 텍스쳐를 가지고 있다
		// 기본 텍스쳐만 가지고 있으며 밉맵 셋팅을 위해 glGenerateMipmap을 호출한다
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}

	// 로드한 다음 데이터 해제
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// OpenGL에게 각 샘플러 택스쳐 셋팅
	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture1"), 0); // set it manually
	ourShader.setInt("ourTexture2", 1); // or with shader class

	// 변환 변수 값 셋팅을 위해 유니폼 정보 가져옴
	//unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

	/// 카메라 정보 셋팅
	sceneCamera = new Camera();
	if (sceneCamera == nullptr)
	{
		cout << "Failed to Init Scene Camera" << endl;
		glfwTerminate();
		return -1;
	}

	// 카메라 객체에 화면 크기 전달
	sceneCamera->Init(SCR_WIDTH, SCR_HEIGHT);

	// 카메라 위치
	sceneCamera->SetCameraPos(vec3(0.0f, 0.0f, 3.0f));
	// cameraPos = vec3(0.0f, 0.0f, 3.0f);

	// 원점을 타겟으로 한다
	sceneCamera->SetTargetPos(vec3(0.0f, 0.0f, 0.0f));
	// cameraTarget = vec3(0.0f, 0.0f, 0.0f);

	// 마우스 입력
	// 커서가 창을 벗어나면 작동 안함
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// 카메라 조작 관련 콜백 등록
	//mainCamera->SetCameraCallback(window);

	// 포인터 정보를 넘겨 람다로 연결해야한다
	glfwSetWindowUserPointer(window, sceneCamera);

	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
	{
		if (Camera *mainCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window)))
			mainCamera->mouse_callback(window, x, y);
	});
	glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset)
	{
		if (Camera *mainCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window)))
			mainCamera->scroll_callback(window, xoffset, yoffset);
	});

	// 커서 움직임 발생 시 호출 할 콜백 등록
	//glfwSetCursorPosCallback(window, mouse_callback);

	// 마우스 스크롤 시 호출 할 콜백 등록
	//glfwSetScrollCallback(window, scroll_callback);

	// 카메라 방향 벡터
	// 첫 오픈 기준으로 화면 쪽이므로 z축 -1.0f 방향이다
	sceneCamera->SetCameraFront(vec3(0.0f, 0.0f, -1.0f));
	//cameraFront = vec3(0.0f, 0.0f, -1.0f);

	// 카메라 업 벡터
	sceneCamera->SetCameraUp(vec3(0.0f, 1.0f, 0.0f));
	//cameraUp = vec3(0.0f, 1.0f, 0.0f);

	mat4 worldMatrix, viewMatrix, projectionMatrix;

	// 월드 매트릭스
	worldMatrix = mat4(1.0f);

	// x축 기준으로 -55도 회전
	//worldMatrix = rotate(worldMatrix, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));

	// 뷰 매트릭스
	sceneCamera->SetCameraLookAt();
	viewMatrix = sceneCamera->GetViewMatrix();
	/*
	viewMatrix = mat4(1.0f);

	// 약간 뒤로 가게 이동
	//viewMatrix = translate(viewMatrix, vec3(0.0f, 0.0f, -3.0f));
	
	viewMatrix = lookAt(cameraPos,					// 카메라 위치
						cameraPos + cameraFront,	// 카메라 방향
						cameraUp);					// 카메라 위
	*/

	// 투영 매트릭스
	sceneCamera->SetCameraPerspective();
	projectionMatrix = sceneCamera->GetProjectionMatrix();
	/*
	projectionMatrix = perspective(
		radians(45.0f),							// 사이각
		(float)SCR_WIDTH/ (float)SCR_HEIGHT,	// 화면 비율 (width / height)
		0.1f,									// 시작 점과 가장 가까운 평면까지의 거리
		100.0f);								// 시작 점과 가장 먼 평면까지의 거리
	*/

	float angle = 0.0f;

	float currentFrame;

	vec3 lightPos(1.2f, 0.0f, 2.0f);
	vec3 lightColor(0.1f, 0.1f, 0.1f);

	// Render loop
	// 윈도우 종료 때까지 계속 반복하면서 렌더링한다
	while (!glfwWindowShouldClose(window))
	{
		//lightPos.x = 1.2f * sin((float)glfwGetTime());
		//lightPos.z = 2.0f * cos((float)glfwGetTime());
		//lightPos.y = 1.2f * sin((float)glfwGetTime());

		//lightColor.x = 1.2f * sin((float)glfwGetTime());
		//lightColor.z = 2.0f * cos((float)glfwGetTime());
		//lightColor.y = 1.2f * sin((float)glfwGetTime());
		// 입력 처리
		processInput(window);

		// 렌더링 처리
		// 클리어 색상 지정
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// GL_COLOR_BUFFER_BIT - 컬러 버퍼 클리어
		// GL_DEPTH_BUFFER_BIT - 깊이 버퍼 클리어
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);

		// 텍스쳐 바인딩
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// 오브젝트 렌더링할 때 우리의 쉐이더 프로그램을 사용하겠다
		ourShader.use();

		// 유니폼 텍스쳐 믹스값 수정
		ourShader.setFloat("mixValue", mixValue);

		// VAO가 하나뿐이므로 매번 바인딩 할 필요는 없지만
		// 좀 더 체계적으로 유지하기 위해 매번 바인딩한다
		// 위에서 0으로 바인딩 해제한 것과 같은 맥락
		glBindVertexArray(VAO);

		// 매 프레임마다 뷰, 투영 매트릭스 수정
		sceneCamera->UpdateComponent();

		viewMatrix = sceneCamera->GetViewMatrix();
		projectionMatrix = sceneCamera->GetProjectionMatrix();
		
		// 카메라 위치 셋팅
		ourShader.setVec3("viewPos", sceneCamera->GetCameraPos());

		// 머테리얼 셋팅
		ourShader.setInt("material.diffuse", 0.8f);
		ourShader.setInt("material.specular", 1);
		ourShader.setFloat("material.shininess", 32.0f);

		// directional light
		ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		// point light 1
		for (int i = 0; i < 4; i++)
		{
			ourShader.setVec3("pointLights[" + to_string(i) + "].position", pointLightPositions[i]);
			ourShader.setVec3("pointLights[" + to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
			ourShader.setVec3("pointLights[" + to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
			ourShader.setVec3("pointLights[" + to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
			ourShader.setFloat("pointLights[" + to_string(i) + "].constant", 1.0f);
			ourShader.setFloat("pointLights[" + to_string(i) + "].linear", 0.09);
			ourShader.setFloat("pointLights[" + to_string(i) + "].quadratic", 0.032);
		}

		// spotLight
		ourShader.setVec3("spotLight.position", sceneCamera->GetCameraPos());
		ourShader.setVec3("spotLight.direction", sceneCamera->GetCameraFront());
		ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		ourShader.setFloat("spotLight.constant", 1.0f);
		ourShader.setFloat("spotLight.linear", 0.09);
		ourShader.setFloat("spotLight.quadratic", 0.032);
		ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// 프레임 계산
		currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 매 프레임마다 변환 행렬 적용
		// 월드, 뷰, 투영 행렬 쉐이더에 적용
		ourShader.setMat4("world", worldMatrix);
		ourShader.setMat4("view", viewMatrix);
		ourShader.setMat4("projection", projectionMatrix);

		// 큐브 여러 개 그리기
		for (unsigned int i = 0; i < 10; i++)
		{
			// 변환 행렬 만든 후
			trans = mat4(1.0f);

			// 큐브 포지션으로 이동 후
			trans = translate(trans, cubePositions[i]);

			// x축 기준으로 -55도 회전
			//trans = rotate(trans, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));

			// 회전 값 셋팅
			//angle = (float)(20 * i);
			
			// 3번째 박스는 시간에 따라 회전
			//if (i % 3 == 0)
				angle = 40 * (float)glfwGetTime();

			//float angle = 20.0f * i;

			// 회전 적용
			trans = rotate(trans, radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			trans = scale(trans, vec3(0.5, 0.5, 0.5));

			// 결과 유니폼에 전송
			ourShader.setMat4("world", trans);

			// 큐브 그리기
			// glDrawArrays - 버텍스만 있으면 그 버텍스들 순서대로 연결한다
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// light object 그리기
		// 이 오브젝트로 나중에 라이트 구성하는 듯
		lightShader.use();

		lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightShader.setMat4("view", viewMatrix);
		lightShader.setMat4("projection", projectionMatrix);

		for (unsigned int i = 0; i < 4; i++)
		{
			trans = mat4(1.0f);
			trans = translate(trans, pointLightPositions[i]);
			trans = scale(trans, vec3(0.2f));

			lightShader.setMat4("world", trans);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/*
		// 오브젝트를 그린다
		// 인덱스 사용이므로 glDrawArrays -> glDrawElements 변경
		// glDrawElements가 사용하는 인덱스는 EBO로 등록한 인덱스 배열이다
		glDrawElements(GL_TRIANGLES,	// 삼각형 그린다
			6,							// 정점의 수
			GL_UNSIGNED_INT,			// 인덱스 배열의 타입
			0);							// 인덱스 배열 시작점
		*/

		/*
		/// 오브젝트 하나 더 만든다
		// 변환 행렬 만든 후
		trans = mat4(1.0f);

		// 위치 이동
		trans = translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));

		// 스케일 변형
		trans = scale(trans, vec3(sin((float)glfwGetTime()), sin((float)glfwGetTime()), sin((float)glfwGetTime())));

		// 결과 유니폼에 전송
		ourShader.setMat4("transform", trans);

		// 오브젝트를 그린다
		// 인덱스 사용이므로 glDrawArrays -> glDrawElements 변경
		// glDrawElements가 사용하는 인덱스는 EBO로 등록한 인덱스 배열이다
		glDrawElements(GL_TRIANGLES,	// 삼각형 그린다
			6,							// 정점의 수
			GL_UNSIGNED_INT,			// 인덱스 배열의 타입
			0);							// 인덱스 배열 시작점
		*/

		// 더블 버퍼로 렌더링 버퍼, 준비 버퍼 둘이 바꾼다
		glfwSwapBuffers(window);

		// 이벤트나 트리거가 발생하는지 체크(키 입력, 마우스 이벤트 등등)
		// 체크 후 윈도우 상태를 업데이트하고 그 상태에 맞는 함수를 호출한다
		glfwPollEvents();
	}

	// 사용한 GL 객체들 해제
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &lightVAO);

	lightShader.Destroy();
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

	// 상하 키 입력 시 텍스쳐 믹스 값 변경
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.001f;
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.001f;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }

	// 카메라 속도 프레임에 맞게 조정 및 조작
	if (sceneCamera != nullptr)
	{
		// 카메라 스피드 조작
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sceneCamera->SetCameraSpeedUp();
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			sceneCamera->SetCameraSpeedDown();
		}

		// 카메라 스피드 프레임에 맞게 계산
		sceneCamera->SetCameraSpeed(deltaTime);

		// 키 입력에 따른 카메라 위치 조정
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			sceneCamera->SetCameraUpDownMove(true);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			sceneCamera->SetCameraUpDownMove(false);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			// 위치 이동으로 인해 매번 방향 벡터 구해줘야 한다
			sceneCamera->SetCameraLeftRightMove(true);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			// 위치 이동으로 인해 매번 방향 벡터 구해줘야 한다
			sceneCamera->SetCameraLeftRightMove(false);
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			sceneCamera->SetCameraTopBottomMove(true);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			sceneCamera->SetCameraTopBottomMove(false);
		}
	}
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}