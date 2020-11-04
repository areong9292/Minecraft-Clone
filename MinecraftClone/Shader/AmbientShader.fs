// �����׸�Ʈ ���̴� �ҽ�
#version 330 core								// ���� 3.3
out vec4 FragColor;								// ������� 4���� ���� �÷� ��

in vec3 vertexColor;							// vertex shader�κ��� �Է��� �޴´�
in vec2 TexCoord;								// �ؽ��� ��ǥ

// sampler2D - �ؽ��� Ÿ��
uniform sampler2D ourTexture1;					// uniform �ڵ忡�� �� ������ ������ ���̴�
uniform sampler2D ourTexture2;

uniform float mixValue;
uniform vec3 lightColor;

void main()
{
	// ourTexture1, ourTexture2 ��� ���
	// ���� �÷� ���� �� �ؽ����� �����̴�
	// 3��° ���� �� ��ŭ �� �ؽ��� ���̸� �������� �Ѵ�
	// 0�� ù��° ��ü, 1�� �ι�° ��ü�̹Ƿ� 0.2�� ù��° �ؽ��� 80%, �ι�° �ؽ��� 20%��
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixValue) * vec4(vertexColor * lightColor, 1.0);;
	//* vec4(vertexColor, 1.0);	// �ؽ��� ����
}