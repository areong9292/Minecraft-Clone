// ���ؽ� ���̴� �ҽ�
#version 330 core								// ���� 3.3
												// �Է� ���� �� ���� �� location �� ���� ����
layout (location = 0) in vec3 aPos;				// �Է����� 3���� ���� aPos �޴´�
layout (location = 1) in vec3 aColor;			// �Է����� 3���� ���� aColor �޴´�
out vec3 vertexColor;							// specify a color output to the fragment shader

uniform mat4 transform;

uniform mat4 world;								// ����
uniform mat4 view;								// ��
uniform mat4 projection;						// ����

void main()
{
	// gl_Position - ���ؽ� ���̴��� ���
	gl_Position = projection * view * world * vec4(aPos, 1.0);	// ���� �Է�(���ؽ�) ������ ����
																// ��ȯ ��� �������� ��ȯ ó��

	vertexColor = aColor;										// ��� �� ����, �� ����� fragment shader�� ���޵ȴ�
}