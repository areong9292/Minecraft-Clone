// glad�� glfw���� include�ؾ��Ѵ�
// glad�� ���� include ���ϵ��� �䱸�Ǵ� OpenGL �����(gl.h����)�� include�Ѵ�
// ���� OpenGL�� �ʿ�� �ϴ�(glfw3�� ����) �ٸ� ������ϵ� ���� ������ glad�� include�ؾ��Ѵ�
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderManager.h"

#include "GLMHeader.h"

// Image Loader Library
// ���� ���� �ҽ� �ڵ� �� �����ϵ��� ��� ������ �����Ͽ�
// ȿ�������� ��� ������ .cpp ���Ϸ� ��ȯ�մϴ�.
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���ؽ�, �ε��� ����
// OpenGL�� ����ȭ �� ��ǥ�� ó���Ѵ�
float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
};

// note that we start from 0!
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

float texCoords[] = {

	0.5f, 1.0f,   // top-center corner 
	1.0f, 0.0f,  // lower-right corner
	0.0f, 0.0f,  // lower-left corner 
};

// �۾� �� ���� ���� üũ�� ����
int  success;
char infoLog[512];

// stores how much we're seeing of either texture
float mixValue = 0.2f;

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
	cout << vec.x << vec.y << vec.z << endl;

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
	GLFWwindow* window = glfwCreateWindow(800, 600,			// width, height
		"LearnOpenGL",		// ������ �̸� 
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
	}

	// ������ ����� ����Ǹ� ����Ʈ�� �׿� �°� ����Ǿ���Ѵ�
	// �ݹ��� �ɾ�ξ� �������� ����� ����Ǿ��� �� �ڵ����� ����Ʈ �����ϰ� �Ѵ�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	ShaderManager ourShader("../Shader/shader.vs", "../Shader/shader.fs");

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

	unsigned int VBO, VAO, EBO;

	// VAO �Ѱ��� �����Ѵ�
	glGenVertexArrays(1, &VAO);

	// VBO �Ѱ��� �����Ѵ�
	glGenBuffers(1, &VBO);

	// EBO �Ѱ��� �����Ѵ�
	glGenBuffers(1, &EBO);

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// GL_ELEMENT_ARRAY_BUFFER�� �ε��� �迭�� ����Ѵ�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,	// �츮�� �����͸� ������ ���� Ÿ��
		sizeof(indices),			// ���� ������ ũ��
		indices,					// ������ ������
		GL_STATIC_DRAW);			// �׷��� ī�尡 �����͸� ��� �ٷ� ���ΰ� ����
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
		8 * sizeof(float),				// ���� �� �޸� ���� ���
		(void*)0);						// ������ ���۰� �����ϴ� ��ġ

	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(
		1,								// �����Ϸ��� ���� �Ӽ�, �÷��� �����ϴµ� ���̴��� location = 1 �̹Ƿ� 1
		3,								// ���ؽ� �Ӽ��� ũ�� - vec3 �̹Ƿ� 3
		GL_FLOAT,						// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
		GL_FALSE,						// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
		8 * sizeof(float),				// ���� �� �޸� ���� ���
		(void*)(3 * sizeof(float)));	// ������ ���۰� �����ϴ� ��ġ - ������ 3�� �ڿ� �÷��̹Ƿ� 3 * float�� ������ ��ġ �ǳʶڴ�

	glEnableVertexAttribArray(1);

	// texture attribute
	glVertexAttribPointer(
		2,								// �����Ϸ��� ���� �Ӽ�, �÷��� �����ϴµ� ���̴��� location = 2 �̹Ƿ� 2
		2,								// ���ؽ� �Ӽ��� ũ�� - vec2 �̹Ƿ� 2
		GL_FLOAT,						// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
		GL_FALSE,						// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
		8 * sizeof(float),				// ���� �� �޸� ���� ���
		(void*)(6 * sizeof(float)));	// ������ ���۰� �����ϴ� ��ġ - ������ 6�� �ڿ� �ؽ����̹Ƿ� 6 * float�� ������ ��ġ �ǳʶڴ�

	glEnableVertexAttribArray(2);


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
		"../Texture/wall.jpg",				// �ؽ��� ���� ���
		&width,								// �ؽ��� width
		&height,							// �ؽ��� height
		&nrChannels,						// �ؽ����� �÷� ä���� ��
		0);

	if (data)
	{
		// ������ �ε��� �ؽ��� ������ �ؽ��ĸ� ������Ų��
		glTexImage2D(GL_TEXTURE_2D,				// �ؽ��� Ÿ�� - ������ ���ε��� �ؽ��� ��ü
						0,						// mipmap level - 0�� �⺻ ����
						GL_RGB,					// �ؽ��ĸ� � �������� ������ ���ΰ�
						width,					// �ؽ��� width
						height,					// �ؽ��� height
						0,						// �̰� �׻� 0
						GL_RGB,					// �̹����� ����
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
		"../Texture/awesomeface.png",		// �ؽ��� ���� ���
		&width,								// �ؽ��� width
		&height,							// �ؽ��� height
		&nrChannels,						// �ؽ����� �÷� ä���� ��
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
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

	// Render loop
	// ������ ���� ������ ��� �ݺ��ϸ鼭 �������Ѵ�
	while (!glfwWindowShouldClose(window))
	{
		// �Է� ó��
		processInput(window);

		// ������ ó��
		// Ŭ���� ���� ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// GL_COLOR_BUFFER_BIT - �÷� ���� Ŭ����
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);

		// �ؽ��� ���ε�
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ������Ʈ �������� �� �츮�� ���̴� ���α׷��� ����ϰڴ�
		ourShader.use();

		// ������ �ؽ��� �ͽ��� ����
		ourShader.setFloat("mixValue", mixValue);

		// ��ȯ ��� ���� ��
		trans = mat4(1.0f);
		trans = translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// ��� �������� ����
		ourShader.setMat4("transform", trans);

		// VAO�� �ϳ����̹Ƿ� �Ź� ���ε� �� �ʿ�� ������
		// �� �� ü�������� �����ϱ� ���� �Ź� ���ε��Ѵ�
		// ������ 0���� ���ε� ������ �Ͱ� ���� �ƶ�
		glBindVertexArray(VAO);

		// ������Ʈ�� �׸���
		// �ε��� ����̹Ƿ� glDrawArrays -> glDrawElements ����
		// glDrawElements�� ����ϴ� �ε����� EBO�� ����� �ε��� �迭�̴�
		glDrawElements(GL_TRIANGLES,	// �ﰢ�� �׸���
			6,							// ������ ��
			GL_UNSIGNED_INT,			// �ε��� �迭�� Ÿ��
			0);							// �ε��� �迭 ������

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

		// ���� ���۷� ������ ����, �غ� ���� ���� �ٲ۴�
		glfwSwapBuffers(window);

		// �̺�Ʈ�� Ʈ���Ű� �߻��ϴ��� üũ(Ű �Է�, ���콺 �̺�Ʈ ���)
		// üũ �� ������ ���¸� ������Ʈ�ϰ� �� ���¿� �´� �Լ��� ȣ���Ѵ�
		glfwPollEvents();
	}

	// ����� GL ��ü�� ����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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
}
