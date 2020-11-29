// �����׸�Ʈ ���̴� �ҽ�
#version 330 core								// ���� 3.3
out vec4 FragColor;								// ������� 4���� ���� �÷� ��

in vec2 TexCoord;								// �ؽ��� ��ǥ
in vec3 Normal;									// �� ���� �븻
in vec3 FragPos;								// ��ȯ�Ǿ� �̵� �� ���ؽ� ��ǥ

// sampler2D - �ؽ��� Ÿ��
uniform sampler2D ourTexture1;					// uniform �ڵ忡�� �� ������ ������ ���̴�
uniform sampler2D ourTexture2;

uniform float mixValue;							// �ؽ��� ���� ��

uniform vec3 viewPos;							// ī�޶� ��ġ

// ���׸���
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
  
uniform Material material;

// Directional Light
struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// ambient - �ֺ��� - ��ü������ ���� ������ ��� ���
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoord));
	
	// diffuse - ���ݻ籤 - ������ ���� ���� ������ ����� ���(180 �������� ���� ���)�� ����Ʈ ����
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	
	// specular - ���ݻ籤 - �ݻ�Ǵ� ������ ����Ʈ ����
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    return (ambient + diffuse + specular);
}

// Attenuation
struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

struct SpotLight {
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

uniform SpotLight spotLight; 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 

	float distance    = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
	
	diffuse  *= intensity;
	specular *= intensity;

	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;
	
    return (ambient + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// 1. Directional Lighting
	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	// 2. Point Lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	// 3. Spot Light
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0);
}