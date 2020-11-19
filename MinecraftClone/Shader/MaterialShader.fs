// �����׸�Ʈ ���̴� �ҽ�
#version 330 core								// ���� 3.3
out vec4 FragColor;								// ������� 4���� ���� �÷� ��

in vec3 vertexColor;							// vertex shader�κ��� �Է��� �޴´�
in vec2 TexCoord;								// �ؽ��� ��ǥ
in vec3 Normal;									// �� ���� �븻
in vec3 FragPos;								// ��ȯ�Ǿ� �̵� �� ���ؽ� ��ǥ

// sampler2D - �ؽ��� Ÿ��
uniform sampler2D ourTexture1;					// uniform �ڵ忡�� �� ������ ������ ���̴�
uniform sampler2D ourTexture2;

uniform float mixValue;							// �ؽ��� ���� ��

uniform vec3 lightPos;							// ���� ��ġ
uniform vec3 lightColor;						// ���� ����
uniform vec3 objectColor;						// ������Ʈ ����
uniform vec3 viewPos;							// ī�޶� ��ġ

// ���׸���
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

// ��
struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light; 

void main()
{
	// ambient - �ֺ��� - ��ü������ ���� ������ ��� ���
    // vec3 ambient = material.ambient * lightColor;
	vec3 ambient  = light.ambient * material.ambient;

	// diffuse - ���ݻ籤 - ������ ���� ���� ������ ����� ���(180 �������� ���� ���)�� ����Ʈ ����
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);				// ���� ���� ��´�
	float diff = max(dot(norm, lightDir), 0.0);					// ���� ���
	// vec3 diffuse = (diff * material.diffuse) * lightColor;		// �� ���� ����
	vec3 diffuse  = light.diffuse * (diff * material.diffuse);

	// specular - ���ݻ籤 - �ݻ�Ǵ� ������ ����Ʈ ����
	vec3 viewDir = normalize(viewPos - FragPos);								// ī�޶� ��ġ ��´�
	vec3 reflectDir = reflect(-lightDir, norm);									// �ݻ� ������ ���Ѵ�
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);	// �ݻ� ����� ī�޶� ��ġ ����, ���̶���Ʈ�� ���� pow ���
	//vec3 specular = material.specular * spec * lightColor;						// �� ���� ����
	vec3 specular = light.specular * (spec * material.specular);  

	// ourTexture1, ourTexture2 ��� ���
	// ���� �÷� ���� �� �ؽ����� �����̴�
	// 3��° ���� �� ��ŭ �� �ؽ��� ���̸� �������� �Ѵ�
	// 0�� ù��° ��ü, 1�� �ι�° ��ü�̹Ƿ� 0.2�� ù��° �ؽ��� 80%, �ι�° �ؽ��� 20%��
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixValue) * vec4(vertexColor * (ambient + diffuse + specular), 1.0);
	//* vec4(vertexColor, 1.0);	// �ؽ��� ����
}