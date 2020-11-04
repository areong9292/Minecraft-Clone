// �����׸�Ʈ ���̴� �ҽ�
#version 330 core								// ���� 3.3
out vec4 FragColor;								// ������� 4���� ���� �÷� ��

in vec3 vertexColor;							// vertex shader�κ��� �Է��� �޴´�
in vec2 TexCoord;								// �ؽ��� ��ǥ
in vec3 Normal;									// �� ���� �븻
in vec3 FragPos;

// sampler2D - �ؽ��� Ÿ��
uniform sampler2D ourTexture1;					// uniform �ڵ忡�� �� ������ ������ ���̴�
uniform sampler2D ourTexture2;

uniform float mixValue;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 lightPos; 

void main()
{
	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// ourTexture1, ourTexture2 ��� ���
	// ���� �÷� ���� �� �ؽ����� �����̴�
	// 3��° ���� �� ��ŭ �� �ؽ��� ���̸� �������� �Ѵ�
	// 0�� ù��° ��ü, 1�� �ι�° ��ü�̹Ƿ� 0.2�� ù��° �ؽ��� 80%, �ι�° �ؽ��� 20%��
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixValue) * vec4(vertexColor * (ambient + diffuse), 1.0);
	//* vec4(vertexColor, 1.0);	// �ؽ��� ����
}