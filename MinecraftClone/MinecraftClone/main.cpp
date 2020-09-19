// glad�� glfw���� include�ؾ��Ѵ�
// glad�� ���� include ���ϵ��� �䱸�Ǵ� OpenGL �����(gl.h����)�� include�Ѵ�
// ���� OpenGL�� �ʿ�� �ϴ�(glfw3�� ����) �ٸ� ������ϵ� ���� ������ glad�� include�ؾ��Ѵ�
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
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
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

		// �̺�Ʈ�� Ʈ���Ű� �߻��ϴ��� üũ(Ű �Է�, ���콺 �̺�Ʈ ���)
		// üũ �� ������ ���¸� ������Ʈ�ϰ� �� ���¿� �´� �Լ��� ȣ���Ѵ�
		glfwPollEvents();

		// ���� ���۷� ������ ����, �غ� ���� ���� �ٲ۴�
		glfwSwapBuffers(window);
	}

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
}