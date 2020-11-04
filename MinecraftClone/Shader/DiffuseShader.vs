// ���ؽ� ���̴� �ҽ�
#version 330 core								// ���� 3.3
												// �Է� ���� �� ���� �� location �� ���� ����
layout (location = 0) in vec3 aPos;				// �Է����� 3���� ���� aPos �޴´�
layout (location = 1) in vec3 aColor;			// �Է����� 3���� ���� aColor �޴´�
layout (location = 2) in vec2 aTexCoord;		// �Է����� 2���� ���� aTexCoord �޴´�
layout (location = 3) in vec3 aNormal;			// �Է����� 3���� ���� aNormal �޴´�

out vec3 vertexColor;							// specify a color output to the fragment shader
out vec2 TexCoord;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;

uniform mat4 world;								// ����
uniform mat4 view;								// ��
uniform mat4 projection;						// ����

void main()
{
	vertexColor = aColor;										// ��� �� ����, �� ����� fragment shader�� ���޵ȴ�
	TexCoord = aTexCoord;										// �ؽ��� ��ǥ ����

	FragPos = vec3(world * vec4(aPos, 1.0));
	//Normal = aNormal;
	Normal = mat3(transpose(inverse(world))) * aNormal;

	// gl_Position - ���ؽ� ���̴��� ���
	gl_Position = projection * view * vec4(FragPos,1.0);		// ���� �Է�(���ؽ�) ������ ����
																// ��ȯ ��� �������� ��ȯ ó��
}