// glad�� glfw���� include�ؾ��Ѵ�
// glad�� ���� include ���ϵ��� �䱸�Ǵ� OpenGL �����(gl.h����)�� include�Ѵ�
// ���� OpenGL�� �ʿ�� �ϴ�(glfw3�� ����) �ٸ� ������ϵ� ���� ������ glad�� include�ؾ��Ѵ�
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���ؽ� �迭 ����
// OpenGL�� ����ȭ �� ��ǥ�� ó���Ѵ�
float vertices[] = {
	-0.5f, -0.5f, 0.0f,		// left
	 0.5f, -0.5f, 0.0f,		// right
	 0.0f,  0.5f, 0.0f		// top
};

// ���ؽ� ���̴� �ҽ�
const char *vertexShaderSource =
"#version 330 core\n"										// ���� 3.3
"layout (location = 0) in vec3 aPos;\n"						// �Է����� 3���� ���� aPos �޴´�
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"		// ���� �Է����� ������ ����
"}\0";														// gl_Position - ���ؽ� ���̴��� ���

// �����׸�Ʈ ���̴� �ҽ�
const char *fragmentShaderSource =
"#version 330 core\n"										// ���� 3.3
"out vec4 FragColor;\n"										// ������� 4���� ���� �÷� ��
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"			// �÷� �� ����
"}\0";

// �۾� �� ���� ���� üũ�� ����
int  success;
char infoLog[512];

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
		1,						// �� ���� ���̴� �ҽ� ������ �Ұų�
		&vertexShaderSource,	// ���̴� �ҽ�
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
		1,						// �� ���� ���̴� �ҽ� ������ �Ұų�
		&fragmentShaderSource,	// ���̴� �ҽ�
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
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// ���̴� Attach
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(shaderProgram);

	// ����üũ
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

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


	/// �׷��� ī�忡 ������ ����
	// vertex buffer objects - VBO
	// ���� ���� ���ؽ��� GPU �޸𸮿� �ѹ��� �ø� �� �ִ�
	// �Ź� ���� �ʿ���� �޸𸮿� �����ϰ� �ִ�

	// CPU -> GPU �޸� ��� �� ��������� ������ ������ ������ �ѹ��� �Ѵ�
	// = ���� ���� �ѹ��� ������
	// �ٸ� OpenGL ��ü ó�� VBO�� ����ũ�� ID�� ������
	// vertex array object - VAO
	// �ε��� �迭 ��ü ����
	unsigned int VBO, VAO;

	// VAO �� �� �����Ѵ�
	glGenVertexArrays(1, &VAO);

	// VBO �Ѱ��� �����Ѵ�
	glGenBuffers(1, &VBO);

	// 1. ���� ���� �迭 ��ü�� ���ε� �� ����
	// 2. ���� ���۸� ���ε��ϰ� ���� �� ����
	// 3. ���� �Ӽ��� �����մϴ�
	// �� ������ �ؾ��ϳ���

	// glBindVertexArray - �� ���ε� �ؼ� VAO�� ����Ѵ�
	// �˾Ƽ� �� ��������
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

	/// ���ؽ� �Ӽ� ����
	// �� ������ �Ӽ��� VBO�� �����ϴ� �޸𸮿��� �����͸� �����´�
	// ���� VBO�� GL_ARRAY_BUFFER�� ���ε��Ǿ� �����Ƿ� ���� �迭�� �����͸� �������� �ȴ�
	glVertexAttribPointer(
						0,						// �����Ϸ��� ���� �Ӽ�, ��ġ�� �����ϴµ� ���̴��� location = 0 �̹Ƿ� 0
						3,						// ���ؽ� �Ӽ��� ũ�� - vec3 �̹Ƿ� 3
						GL_FLOAT,				// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
						GL_FALSE,				// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
						3 * sizeof(float),		// ���� �� �޸� ���� ���
						(void*)0);				// ������ ���۰� �����ϴ� ��ġ

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

		// ������Ʈ �������� �� �츮�� ���̴� ���α׷��� ����ϰڴ�
		glUseProgram(shaderProgram);

		// VAO�� �ϳ����̹Ƿ� �Ź� ���ε� �� �ʿ�� ������
		// �� �� ü�������� �����ϱ� ���� �Ź� ���ε��Ѵ�
		glBindVertexArray(VAO);

		// ������Ʈ�� �׸���
		glDrawArrays(GL_TRIANGLES,	// �ﰢ�� �׸���
			0,						// ������ ������
			3);						// ������ ��

		// ���� ���۷� ������ ����, �غ� ���� ���� �ٲ۴�
		glfwSwapBuffers(window);

		// �̺�Ʈ�� Ʈ���Ű� �߻��ϴ��� üũ(Ű �Է�, ���콺 �̺�Ʈ ���)
		// üũ �� ������ ���¸� ������Ʈ�ϰ� �� ���¿� �´� �Լ��� ȣ���Ѵ�
		glfwPollEvents();
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

// ���̴� ����, ���� �� ��ũ
void SetShader()
{
	
}