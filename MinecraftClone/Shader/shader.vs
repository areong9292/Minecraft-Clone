// ���ؽ� ���̴� �ҽ�
#version 330 core								// ���� 3.3
												// �Է� ���� �� ���� �� location �� ���� ����
layout (location = 0) in vec3 aPos;				// �Է����� 3���� ���� aPos �޴´�
layout (location = 1) in vec3 aColor;			// �Է����� 3���� ���� aColor �޴´�
layout (location = 2) in vec2 aTexCoord;		// �Է����� 2���� ���� aTexCoord �޴´�
out vec3 vertexColor;							// specify a color output to the fragment shader
out vec2 TexCoord;

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
	TexCoord = aTexCoord;										// �ؽ��� ��ǥ ����
}