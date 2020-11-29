// 프레그먼트 쉐이더 소스
#version 330 core								// 버전 3.3
out vec4 FragColor;								// 출력으로 4차원 벡터 컬러 값

in vec2 TexCoord;								// 텍스쳐 좌표
in vec3 Normal;									// 한 면의 노말
in vec3 FragPos;								// 변환되어 이동 된 버텍스 좌표

// sampler2D - 텍스쳐 타입
uniform sampler2D ourTexture1;					// uniform 코드에서 이 변수를 제어할 것이다
uniform sampler2D ourTexture2;

uniform float mixValue;							// 텍스쳐 블랜딩 값

uniform vec3 viewPos;							// 카메라 위치

// 머테리얼
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

	// ambient - 주변광 - 전체적으로 조명 색상을 얇게 깐다
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoord));
	
	// diffuse - 난반사광 - 법선과 빛의 방향 내적이 양수인 경우(180 안쪽으로 들어올 경우)만 라이트 적용
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	
	// specular - 정반사광 - 반사되는 지점에 라이트 적용
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