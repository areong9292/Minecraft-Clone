// �����׸�Ʈ ���̴� �ҽ�
#version 330 core								// ���� 3.3
out vec4 FragColor;								// ������� 4���� ���� �÷� ��
in vec3 vertexColor;							// vertex shader�κ��� �Է��� �޴´�
uniform vec4 ourColor;							// uniform �ڵ忡�� �� ������ ������ ���̴�

void main()
{
   FragColor = vec4(vertexColor, 1.0);			// �÷� �� ����
}