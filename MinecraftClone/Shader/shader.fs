// �����׸�Ʈ ���̴� �ҽ�
#version 330 core								// ���� 3.3
out vec4 FragColor;								// ������� 4���� ���� �÷� ��

in vec3 vertexColor;							// vertex shader�κ��� �Է��� �޴´�
in vec2 TexCoord;								// �ؽ��� ��ǥ

// sampler2D - �ؽ��� Ÿ��
uniform sampler2D ourTexture;					// uniform �ڵ忡�� �� ������ ������ ���̴�

void main()
{
   FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);	// �ؽ��� ����
}