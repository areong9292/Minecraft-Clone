// �����׸�Ʈ ���̴� �ҽ�
#version 330 core								// ���� 3.3
out vec4 FragColor;								// ������� 4���� ���� �÷� ��

in vec3 vertexColor;							// vertex shader�κ��� �Է��� �޴´�
in vec2 TexCoord;								// �ؽ��� ��ǥ

uniform vec3 lightColor;

void main()
{
	FragColor = vec4(vertexColor * lightColor, 1.0);
	//* vec4(vertexColor, 1.0);	// �ؽ��� ����
}