// glad�� glfw���� include�ؾ��Ѵ�
// glad�� ���� include ���ϵ��� �䱸�Ǵ� OpenGL �����(gl.h����)�� include�Ѵ�
// ���� OpenGL�� �ʿ�� �ϴ�(glfw3�� ����) �ٸ� ������ϵ� ���� ������ glad�� include�ؾ��Ѵ�
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���ؽ�, �ε��� ����
// OpenGL�� ����ȭ �� ��ǥ�� ó���Ѵ�
float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

// note that we start from 0!
unsigned int indices[] = {
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
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
	glVertexAttribPointer(
						0,						// �����Ϸ��� ���� �Ӽ�, ��ġ�� �����ϴµ� ���̴��� location = 0 �̹Ƿ� 0
						3,						// ���ؽ� �Ӽ��� ũ�� - vec3 �̹Ƿ� 3
						GL_FLOAT,				// ���ؽ� ������ ���� - vec3 �̹Ƿ� float
						GL_FALSE,				// ������ ����ȭ ���� - �̹� ����ȭ�� �־����Ƿ� false
						3 * sizeof(float),		// ���� �� �޸� ���� ���
						(void*)0);				// ������ ���۰� �����ϴ� ��ġ

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		// ������ 0���� ���ε� ������ �Ͱ� ���� �ƶ�
		glBindVertexArray(VAO);

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
	glDeleteProgram(shaderProgram);


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
