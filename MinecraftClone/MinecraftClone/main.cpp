// glad�� glfw���� include�ؾ��Ѵ�
// glad�� ���� include ���ϵ��� �䱸�Ǵ� OpenGL �����(gl.h����)�� include�Ѵ�
// ���� OpenGL�� �ʿ�� �ϴ�(glfw3�� ����) �ٸ� ������ϵ� ���� ������ glad�� include�ؾ��Ѵ�
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderManager.h"

#include <GLMHeader.h>

#include "Camera.h"

#include <string>

// Image Loader Library
// ���� ���� �ҽ� �ڵ� �� �����ϵ��� ��� ������ �����Ͽ�
// ȿ�������� ��� ������ .cpp ���Ϸ� ��ȯ�մϴ�.
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// ���ؽ�, �ε��� ����
// OpenGL�� ����ȭ �� ��ǥ�� ó���Ѵ�
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

// ť��� ��ġ
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

// ����Ʈ ��ġ
vec3 pointLightPositions[] = {
	vec3(0.7f,  0.2f,  2.0f),
	vec3(2.3f, -3.3f, -4.0f),
	vec3(-4.0f,  2.0f, -12.0f),
	vec3(0.0f,  0.0f, -3.0f)
};

// �۾� �� ���� ���� üũ�� ����
int  success;
char infoLog[512];

// stores how much we're seeing of either texture
float mixValue = 0.2f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/// ī�޶� ���� ����
Camera* sceneCamera = nullptr;
/*
// ī�޶� ��ġ
vec3 cameraPos;

// ī�޶� Ÿ��
vec3 cameraTarget;

// ī�޶� ���� ����
vec3 cameraFront;

// ī�޶� �� ����
vec3 cameraUp;

// ī�޶� �̵� �ӵ�
float cameraSpeed = 0.05f;

/// ������ ���
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
double lastX = 0;
double lastY = 0;
float m_yaw = -90.0f;
float m_pitch = 0.0f;
float Zoom = 45.0f;
*/
/// ������ ���
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	/// glm �׽�Ʈ
	// ����, ��� ����
	vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	mat4 trans = glm::mat4(1.0f);

	// 1,1,0 �̵���� ����
	trans = translate(trans, vec3(1.0f, 1.0f, 0.0f));

	// ���� �̵�
	vec = trans * vec;

	// ���� �̵� ���
	//cout << vec.x << vec.y << vec.z << endl;

	// ���� ��� ����
	trans = mat4(1.0f);

	// z��(vec3(0.0, 0.0, 1.0)) �������� 90��(radians(90.0f)) ȸ���ϴ� ȸ����ĸ����
	trans = rotate(trans, radians(90.0f), vec3(0.0, 0.0, 1.0));

	// xyz�� 0.5�� ��ȯ���
	trans = scale(trans, vec3(0.5, 0.5, 0.5));


	// GLFW Window�� �ν��Ͻ�ȭ�Ѵ�
	// GLFW init
	glfwInit();

	// glfwWindowHint - GLFW ������ �� �� ����ϴ� �޼ҵ�
	// ù��° ���ڴ� �ɼ�, �ι�° ���ڴ� �ش� �ɼ��� ���̴�

	// OpenGL ���� 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	// MacOS������ �Ʒ� ������ �߰��ؾ��Ѵ�
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// ������ ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,			// width, height
										"LearnOpenGL",						// ������ �̸� 
										NULL, NULL);

	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// ���� �����忡 main context ������ ������ �Ѵ�
	glfwMakeContextCurrent(window);

	// GLAD�� �Լ� �����͸� �����Ѵ�
	// �׷��Ƿ� OpenGL �Լ����� ȣ���ϱ� ���� GLAD�� �ʱ�ȭ�Ѵ�
	// glfwGetProcAddress - �Լ� ������ ��Ƶ� �ּ�
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		return -1;
	}

	// ���� ����� �Ѵ�
	glEnable(GL_DEPTH_TEST);

	// ������ ����� ����Ǹ� ����Ʈ�� �׿� �°� ����Ǿ���Ѵ�
	// �ݹ��� �ɾ�ξ� �������� ����� ����Ǿ��� �� �ڵ����� ����Ʈ �����ϰ� �Ѵ�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	ShaderManager ourShader(ShaderManager::ShaderType::MULTIPLELIGHTS);
	ShaderManager lightShader(ShaderManager::ShaderType::DEFAULT);

	/// �׷��� ī�忡 ������ ����
	// vertex buffer objects - VBO
	// ���� ���� ���ؽ��� GPU �޸𸮿� �ѹ��� �ø� �� �ִ�
	// �Ź� ���� �ʿ���� �޸𸮿� �����ϰ� �ִ�
	// CPU -> GPU �޸� ��� �� ��������� ������ ������ ������ �ѹ��� �Ѵ�
	// = ���� ���� �ѹ��� ������
	// �ٸ� OpenGL ��ü ó�� ����ũ�� ID�� ������

	// VBO�� �����ϴ� �迭
	// vertex array object - VAO

	// �ε��� �迭
	// element buffer objects - EBO

	unsigned int VBO, VAO;// , EBO;

	// VAO �Ѱ��� �����Ѵ�
	glGenVertexArrays(1, &VAO);

	// VBO �Ѱ��� �����Ѵ�
	glGenBuffers(1, &VBO);

	// EBO �Ѱ��� �����Ѵ�
	//glGenBuffers(1, &EBO);

	// 1. ���� ���� �迭 ��ü�� ���ε� �� ����
	// 2. ���� ���۸� ���ε��ϰ� ���� �� ����
	// 3. ���� �Ӽ��� �����մϴ�
	// �� ������ �ؾ��ϳ���

	// glBindVertexArray - �� ���ε� �ؼ� VAO�� ����Ѵ�
	// �׷��� VBO�� �˾Ƽ� �� ������ ���� �迭 ����ؼ� �����Ѵ�
	glBindVertexArray(VAO);

	// OpenGL�� ���� ��ü���� �پ��� Ÿ���� ������
	// VBO�� GL_ARRAY_BUFFER Ÿ���� ������
	// OpenGL�� ���۰� ���� �ٸ� Ÿ���̶�� �ѹ��� ���� ���۸� ���ε��� �� �ִ�
	// glBindBuffer �޼ҵ�� VBO�� GL_ARRAY_BUFFER Ÿ�ٿ� ���ε��Ѵ�
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// glBufferData �޼ҵ�� ������ ������ ���ؽ� ������
	// ���� �޸𸮿� ������ �� �ִ�
	glBufferData(GL_ARRAY_BUFFER,			// �츮�� �����͸� ������ ���� Ÿ��
		sizeof(vertices),			// ���� ������ ũ��
		vertices,					// ������ ������
		GL_STATIC_DRAW);			// �׷��� ī�尡 �����͸� ��� �ٷ� ���ΰ� ����
									// GL_STATIC_DRAW - �ѹ� ����, ���� �� ���

	// EBO�� GL_ELEMENT_ARRAY_BUFFER�� ���
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// GL_ELEMENT_ARRAY_BUFFER�� �ε��� �迭�� ����Ѵ�
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,	// �츮�� �����͸� ������ ���� Ÿ��
	//	sizeof(indices),			// ���� ������ ũ��
	//	indices,					// ������ ������
	//	GL_STATIC_DRAW);			// �׷��� ī�尡 �����͸� ��� �ٷ� ���ΰ� ����
									// GL_STATIC_DRAW - �ѹ� ����, ���� �� ���

	/// ���ؽ� �Ӽ� ����
	// �� ������ �Ӽ��� VBO�� �����ϴ� �޸𸮿��� �����͸� �����´�
	// ���� VBO�� GL_ARRAY_BUFFER�� ���ε��Ǿ� �����Ƿ� ���� �迭�� �����͸� �������� �ȴ�
	// position attribute
	glVertexAttribPointer(
		0,								// �����Ϸ��� ���� �Ӽ�, ��ġ�� �����ϴµ� ���̴��� location = 0 �̹Ƿ� 0
		3,								// ���ؽ� �Ӽ��� ũ�� - vec3 �̹Ƿ� 3
		GL_FLOAT,						// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
		GL_FALSE,						// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
		verticesOffset * sizeof(float),	// ���� �� �޸� ���� ���
		(void*)0);						// ������ ���۰� �����ϴ� ��ġ

	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(
		1,								// �����Ϸ��� ���� �Ӽ�, �÷��� �����ϴµ� ���̴��� location = 1 �̹Ƿ� 1
		3,								// ���ؽ� �Ӽ��� ũ�� - vec3 �̹Ƿ� 3
		GL_FLOAT,						// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
		GL_FALSE,						// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
		verticesOffset * sizeof(float),	// ���� �� �޸� ���� ���
		(void*)(3 * sizeof(float)));	// ������ ���۰� �����ϴ� ��ġ - ������ 3�� �ڿ� �÷��̹Ƿ� 3 * float�� ������ ��ġ �ǳʶڴ�

	glEnableVertexAttribArray(1);

	// texture attribute
	glVertexAttribPointer(
		2,								// �����Ϸ��� ���� �Ӽ�, �÷��� �����ϴµ� ���̴��� location = 2 �̹Ƿ� 2
		2,								// ���ؽ� �Ӽ��� ũ�� - vec2 �̹Ƿ� 2
		GL_FLOAT,						// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
		GL_FALSE,						// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
		verticesOffset * sizeof(float),	// ���� �� �޸� ���� ���
		(void*)(6 * sizeof(float)));	// ������ ���۰� �����ϴ� ��ġ - ������ 6�� �ڿ� �ؽ����̹Ƿ� 6 * float�� ������ ��ġ �ǳʶڴ�

	glEnableVertexAttribArray(2);

	// normal attribute
	glVertexAttribPointer(
		3,								// �����Ϸ��� ���� �Ӽ�, �븻�� �����ϴµ� ���̴��� location = 3 �̹Ƿ� 3
		3,								// ���ؽ� �Ӽ��� ũ�� - vec3 �̹Ƿ� 3
		GL_FLOAT,						// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
		GL_FALSE,						// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
		verticesOffset * sizeof(float),	// ���� �� �޸� ���� ���
		(void*)(8 * sizeof(float)));	// ������ ���۰� �����ϴ� ��ġ - ������ 8�� �ڿ� �ؽ����̹Ƿ� 8 * float�� ������ ��ġ �ǳʶڴ�

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
	// glVertexAttribPointer ȣ���� VBO��
	// the vertex attribute's bound vertex buffer object �� ����Ѵ�
	// ���� �����ϰ� ���ε��� ������ �� �ִ�
	// -> �̹� ��ϵǾ��� ������ ���� �����ϴ�...?
	// ã�ƺ��� �������� ���� null ���� ���ε� �ϴ� ��?

	// We��re done uploading, so unbind the buffer for safety.
	// ������ ���� �̹� ���ε� �� ���۸� ����ε��Ѵ�
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember:
	// do NOT unbind the EBO while a VAO is active
	// as the bound element buffer object is stored in the VAO;
	// keep the EBO bound.
	// ���ε� �� EBO�� VAO�� ����ǹǷ�
	// VAO�� Ȱ��ȭ�Ǿ��ִ� ���� EBO�� �������� ���ʽÿ�.
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards
	// VAO ���� ���ε� ������ �� �ִ�
	// so other VAO calls won't accidentally modify this VAO, but this rarely happens.
	// �׷��� �ٸ� VAO ȣ����� �Ǽ��� �� VAO�� �������� ������, ���� �Ͼ �� �ִ�
	// Modifying other VAOs requires a call to glBindVertexArray anyways
	// �ٸ� VAO�� �����ϴ� �͵� glBindVertexArray�� ȣ��Ǿ��Ѵ�
	// so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// �׷��� �Ϲ������δ� VAO (�Ǵ� VBO)�� ���������� �ʿ����� ���� ���
	// ���ε��� �������� �ʽ��ϴ�.

	// �� ������ �����ϸ� VAO�� ���ε� �Ǿ�������
	// ���� �ٸ� VAO�� �� VAO�� �ǵ����� �ʰ����� Ȥ�ó� �ϴ� �Ǽ���
	// �츮�� �׸����� �ϴ� VBO�� ������ VAO�� ������ �� �ִ�
	// �Ǽ��� ���ϱ� ���� ���ε��� �����Ѵ�
	glBindVertexArray(0);

	// wireframe polygons �� �׸����� �ּ� ����
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/// �ؽ��� �ε� �� ����
	// �ؽ��� ��ü ����
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);

	// ������ ��ü�� GL_TEXTURE_2D�� ���ε��Ѵ�
	glBindTexture(GL_TEXTURE_2D, texture1);

	// S - ������, T - ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// ���� �ؽ��� ������ GL_TEXTURE_BORDER_COLOR �� ���
	// �ٱ� ���� �����ؾ��Ѵ�
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// GL_NEAREST - ���� ����� ������ ����
	// GL_LINEAR - ��ó ����� �������� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �ؽ��� ������ �ε�
	int width, height, nrChannels;

	// ���Ϲ���
	stbi_set_flip_vertically_on_load(true);

	// �ؽ��� ������ �ҷ�����
	unsigned char* data = stbi_load(
		"../Texture/container2.png",		// �ؽ��� ���� ���
		&width,								// �ؽ��� width
		&height,							// �ؽ��� height
		&nrChannels,						// �ؽ����� �÷� ä���� ��
		0);

	if (data)
	{
		// ������ �ε��� �ؽ��� ������ �ؽ��ĸ� ������Ų��
		glTexImage2D(GL_TEXTURE_2D,				// �ؽ��� Ÿ�� - ������ ���ε��� �ؽ��� ��ü
						0,						// mipmap level - 0�� �⺻ ����
						GL_RGBA,				// �ؽ��ĸ� � �������� ������ ���ΰ�
						width,					// �ؽ��� width
						height,					// �ؽ��� height
						0,						// �̰� �׻� 0
						GL_RGBA,				// �̹����� ����
						GL_UNSIGNED_BYTE,		// ������ ����
						data);					// ���� �̹��� ������

		// glTexImage2D ȣ�� �Ŀ���
		// ���ε� �� �ؽ��� ������Ʈ�� �ؽ��ĸ� ������ �ִ�
		// �⺻ �ؽ��ĸ� ������ ������ �Ӹ� ������ ���� glGenerateMipmap�� ȣ���Ѵ�
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}

	// �ε��� ���� ������ ����
	stbi_image_free(data);

	// 2��° �ؽ��� ��ü ����
	glGenTextures(1, &texture2);

	// ������ ��ü�� GL_TEXTURE_2D�� ���ε��Ѵ�
	glBindTexture(GL_TEXTURE_2D, texture2);

	// S - ������, T - ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ���� �ؽ��� ������ GL_TEXTURE_BORDER_COLOR �� ���
	// �ٱ� ���� �����ؾ��Ѵ�
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// GL_NEAREST - ���� ����� ������ ����
	// GL_LINEAR - ��ó ����� �������� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �ؽ��� ������ �ε�
	data = stbi_load(
		"../Texture/container2_specular.png",		// �ؽ��� ���� ���
		&width,										// �ؽ��� width
		&height,									// �ؽ��� height
		&nrChannels,								// �ؽ����� �÷� ä���� ��
		0);

	if (data)
	{
		// ������ �ε��� �ؽ��� ������ �ؽ��ĸ� ������Ų��
		glTexImage2D(GL_TEXTURE_2D,	// �ؽ��� Ÿ�� - ������ ���ε��� �ؽ��� ��ü
			0,						// mipmap level - 0�� �⺻ ����
			GL_RGBA,				// �ؽ��ĸ� � �������� ������ ���ΰ� - A ���� �߰�
			width,					// �ؽ��� width
			height,					// �ؽ��� height
			0,						// �̰� �׻� 0
			GL_RGBA,				// �̹����� ���� - A ���� �߰�
			GL_UNSIGNED_BYTE,		// ������ ����
			data);					// ���� �̹��� ������

		// glTexImage2D ȣ�� �Ŀ���
		// ���ε� �� �ؽ��� ������Ʈ�� �ؽ��ĸ� ������ �ִ�
		// �⺻ �ؽ��ĸ� ������ ������ �Ӹ� ������ ���� glGenerateMipmap�� ȣ���Ѵ�
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}

	// �ε��� ���� ������ ����
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// OpenGL���� �� ���÷� �ý��� ����
	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture1"), 0); // set it manually
	ourShader.setInt("ourTexture2", 1); // or with shader class

	// ��ȯ ���� �� ������ ���� ������ ���� ������
	//unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

	/// ī�޶� ���� ����
	sceneCamera = new Camera();
	if (sceneCamera == nullptr)
	{
		cout << "Failed to Init Scene Camera" << endl;
		glfwTerminate();
		return -1;
	}

	// ī�޶� ��ü�� ȭ�� ũ�� ����
	sceneCamera->Init(SCR_WIDTH, SCR_HEIGHT);

	// ī�޶� ��ġ
	sceneCamera->SetCameraPos(vec3(0.0f, 0.0f, 3.0f));
	// cameraPos = vec3(0.0f, 0.0f, 3.0f);

	// ������ Ÿ������ �Ѵ�
	sceneCamera->SetTargetPos(vec3(0.0f, 0.0f, 0.0f));
	// cameraTarget = vec3(0.0f, 0.0f, 0.0f);

	// ���콺 �Է�
	// Ŀ���� â�� ����� �۵� ����
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// ī�޶� ���� ���� �ݹ� ���
	//mainCamera->SetCameraCallback(window);

	// ������ ������ �Ѱ� ���ٷ� �����ؾ��Ѵ�
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

	// Ŀ�� ������ �߻� �� ȣ�� �� �ݹ� ���
	//glfwSetCursorPosCallback(window, mouse_callback);

	// ���콺 ��ũ�� �� ȣ�� �� �ݹ� ���
	//glfwSetScrollCallback(window, scroll_callback);

	// ī�޶� ���� ����
	// ù ���� �������� ȭ�� ���̹Ƿ� z�� -1.0f �����̴�
	sceneCamera->SetCameraFront(vec3(0.0f, 0.0f, -1.0f));
	//cameraFront = vec3(0.0f, 0.0f, -1.0f);

	// ī�޶� �� ����
	sceneCamera->SetCameraUp(vec3(0.0f, 1.0f, 0.0f));
	//cameraUp = vec3(0.0f, 1.0f, 0.0f);

	mat4 worldMatrix, viewMatrix, projectionMatrix;

	// ���� ��Ʈ����
	worldMatrix = mat4(1.0f);

	// x�� �������� -55�� ȸ��
	//worldMatrix = rotate(worldMatrix, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));

	// �� ��Ʈ����
	sceneCamera->SetCameraLookAt();
	viewMatrix = sceneCamera->GetViewMatrix();
	/*
	viewMatrix = mat4(1.0f);

	// �ణ �ڷ� ���� �̵�
	//viewMatrix = translate(viewMatrix, vec3(0.0f, 0.0f, -3.0f));
	
	viewMatrix = lookAt(cameraPos,					// ī�޶� ��ġ
						cameraPos + cameraFront,	// ī�޶� ����
						cameraUp);					// ī�޶� ��
	*/

	// ���� ��Ʈ����
	sceneCamera->SetCameraPerspective();
	projectionMatrix = sceneCamera->GetProjectionMatrix();
	/*
	projectionMatrix = perspective(
		radians(45.0f),							// ���̰�
		(float)SCR_WIDTH/ (float)SCR_HEIGHT,	// ȭ�� ���� (width / height)
		0.1f,									// ���� ���� ���� ����� �������� �Ÿ�
		100.0f);								// ���� ���� ���� �� �������� �Ÿ�
	*/

	float angle = 0.0f;

	float currentFrame;

	vec3 lightPos(1.2f, 0.0f, 2.0f);
	vec3 lightColor(0.1f, 0.1f, 0.1f);

	// Render loop
	// ������ ���� ������ ��� �ݺ��ϸ鼭 �������Ѵ�
	while (!glfwWindowShouldClose(window))
	{
		//lightPos.x = 1.2f * sin((float)glfwGetTime());
		//lightPos.z = 2.0f * cos((float)glfwGetTime());
		//lightPos.y = 1.2f * sin((float)glfwGetTime());

		//lightColor.x = 1.2f * sin((float)glfwGetTime());
		//lightColor.z = 2.0f * cos((float)glfwGetTime());
		//lightColor.y = 1.2f * sin((float)glfwGetTime());
		// �Է� ó��
		processInput(window);

		// ������ ó��
		// Ŭ���� ���� ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// GL_COLOR_BUFFER_BIT - �÷� ���� Ŭ����
		// GL_DEPTH_BUFFER_BIT - ���� ���� Ŭ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);

		// �ؽ��� ���ε�
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ������Ʈ �������� �� �츮�� ���̴� ���α׷��� ����ϰڴ�
		ourShader.use();

		// ������ �ؽ��� �ͽ��� ����
		ourShader.setFloat("mixValue", mixValue);

		// VAO�� �ϳ����̹Ƿ� �Ź� ���ε� �� �ʿ�� ������
		// �� �� ü�������� �����ϱ� ���� �Ź� ���ε��Ѵ�
		// ������ 0���� ���ε� ������ �Ͱ� ���� �ƶ�
		glBindVertexArray(VAO);

		// �� �����Ӹ��� ��, ���� ��Ʈ���� ����
		sceneCamera->UpdateComponent();

		viewMatrix = sceneCamera->GetViewMatrix();
		projectionMatrix = sceneCamera->GetProjectionMatrix();
		
		// ī�޶� ��ġ ����
		ourShader.setVec3("viewPos", sceneCamera->GetCameraPos());

		// ���׸��� ����
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

		// ������ ���
		currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// �� �����Ӹ��� ��ȯ ��� ����
		// ����, ��, ���� ��� ���̴��� ����
		ourShader.setMat4("world", worldMatrix);
		ourShader.setMat4("view", viewMatrix);
		ourShader.setMat4("projection", projectionMatrix);

		// ť�� ���� �� �׸���
		for (unsigned int i = 0; i < 10; i++)
		{
			// ��ȯ ��� ���� ��
			trans = mat4(1.0f);

			// ť�� ���������� �̵� ��
			trans = translate(trans, cubePositions[i]);

			// x�� �������� -55�� ȸ��
			//trans = rotate(trans, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));

			// ȸ�� �� ����
			//angle = (float)(20 * i);
			
			// 3��° �ڽ��� �ð��� ���� ȸ��
			//if (i % 3 == 0)
				angle = 40 * (float)glfwGetTime();

			//float angle = 20.0f * i;

			// ȸ�� ����
			trans = rotate(trans, radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			trans = scale(trans, vec3(0.5, 0.5, 0.5));

			// ��� �������� ����
			ourShader.setMat4("world", trans);

			// ť�� �׸���
			// glDrawArrays - ���ؽ��� ������ �� ���ؽ��� ������� �����Ѵ�
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// light object �׸���
		// �� ������Ʈ�� ���߿� ����Ʈ �����ϴ� ��
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
		// ������Ʈ�� �׸���
		// �ε��� ����̹Ƿ� glDrawArrays -> glDrawElements ����
		// glDrawElements�� ����ϴ� �ε����� EBO�� ����� �ε��� �迭�̴�
		glDrawElements(GL_TRIANGLES,	// �ﰢ�� �׸���
			6,							// ������ ��
			GL_UNSIGNED_INT,			// �ε��� �迭�� Ÿ��
			0);							// �ε��� �迭 ������
		*/

		/*
		/// ������Ʈ �ϳ� �� �����
		// ��ȯ ��� ���� ��
		trans = mat4(1.0f);

		// ��ġ �̵�
		trans = translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));

		// ������ ����
		trans = scale(trans, vec3(sin((float)glfwGetTime()), sin((float)glfwGetTime()), sin((float)glfwGetTime())));

		// ��� �������� ����
		ourShader.setMat4("transform", trans);

		// ������Ʈ�� �׸���
		// �ε��� ����̹Ƿ� glDrawArrays -> glDrawElements ����
		// glDrawElements�� ����ϴ� �ε����� EBO�� ����� �ε��� �迭�̴�
		glDrawElements(GL_TRIANGLES,	// �ﰢ�� �׸���
			6,							// ������ ��
			GL_UNSIGNED_INT,			// �ε��� �迭�� Ÿ��
			0);							// �ε��� �迭 ������
		*/

		// ���� ���۷� ������ ����, �غ� ���� ���� �ٲ۴�
		glfwSwapBuffers(window);

		// �̺�Ʈ�� Ʈ���Ű� �߻��ϴ��� üũ(Ű �Է�, ���콺 �̺�Ʈ ���)
		// üũ �� ������ ���¸� ������Ʈ�ϰ� �� ���¿� �´� �Լ��� ȣ���Ѵ�
		glfwPollEvents();
	}

	// ����� GL ��ü�� ����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &lightVAO);

	lightShader.Destroy();
	ourShader.Destroy();

	// GLFW �ڿ��� �����Ѵ�
	glfwTerminate();


	return 0;
}

// ������ ������ ���� �� ȣ��Ǵ� �ݹ�
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ����Ʈ ���� - ����Ʈ�� glfw���� ���� �������� ������ �� �ִ�
	// ������ ��, ������ �� ������ ũ��(�ȼ�)�� �����Ѵ�
	glViewport(0, 0,			// ���� �� ��ǥ
		width, height);			// width, height
}

// �Է� ó�� �޼ҵ�
void processInput(GLFWwindow* window)
{
	// esc Ű ������ ������ ���� ����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// ���� Ű �Է� �� �ؽ��� �ͽ� �� ����
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

	// ī�޶� �ӵ� �����ӿ� �°� ���� �� ����
	if (sceneCamera != nullptr)
	{
		// ī�޶� ���ǵ� ����
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sceneCamera->SetCameraSpeedUp();
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			sceneCamera->SetCameraSpeedDown();
		}

		// ī�޶� ���ǵ� �����ӿ� �°� ���
		sceneCamera->SetCameraSpeed(deltaTime);

		// Ű �Է¿� ���� ī�޶� ��ġ ����
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
			// ��ġ �̵����� ���� �Ź� ���� ���� ������� �Ѵ�
			sceneCamera->SetCameraLeftRightMove(true);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			// ��ġ �̵����� ���� �Ź� ���� ���� ������� �Ѵ�
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