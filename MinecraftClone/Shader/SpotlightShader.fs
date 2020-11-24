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
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
  
uniform Material material;

// ��
struct Light {
	vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
    float outerCutOff;
};

uniform Light light; 

void main()
{
	// ambient - �ֺ��� - ��ü������ ���� ������ ��� ���
    // vec3 ambient = material.ambient * lightColor;
	vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoord));

	// diffuse - ���ݻ籤 - ������ ���� ���� ������ ����� ���(180 �������� ���� ���)�� ����Ʈ ����
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);			// ���� ���� ��´�
	float diff = max(dot(norm, lightDir), 0.0);						// ���� ���
	// vec3 diffuse = (diff * material.diffuse) * lightColor;		// �� ���� ����
	vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	// specular - ���ݻ籤 - �ݻ�Ǵ� ������ ����Ʈ ����
	vec3 viewDir = normalize(viewPos - FragPos);								// ī�޶� ��ġ ��´�
	vec3 reflectDir = reflect(-lightDir, norm);									// �ݻ� ������ ���Ѵ�
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);	// �ݻ� ����� ī�޶� ��ġ ����, ���̶���Ʈ�� ���� pow ���
	//vec3 specular = material.specular * spec * lightColor;						// �� ���� ����
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
	
	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 

	// we'll leave ambient unaffected so we always have a little light.
	diffuse  *= intensity;
	specular *= intensity;

	float distance    = length(lightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;
	
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixValue) * vec4(ambient + diffuse + specular, 1.0);
}