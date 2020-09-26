// ���ؽ� ���̴� �ҽ�
#version 330 core								// ���� 3.3
												// �Է� ���� �� ���� �� location �� ���� ����
layout (location = 0) in vec3 aPos;				// �Է����� 3���� ���� aPos �޴´�
layout (location = 1) in vec3 aColor;			// �Է����� 3���� ���� aColor �޴´�
out vec3 vertexColor;							// specify a color output to the fragment shader

void main()
{
   gl_Position = vec4(aPos, 1.0);				// ���� �Է�(���ؽ�) ������ ����
	vertexColor = aColor;						// ��� �� ����, �� ����� fragment shader�� ���޵ȴ�
}												// gl_Position - ���ؽ� ���̴��� ���